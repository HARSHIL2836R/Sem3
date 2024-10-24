
#!/usr/bin/python3

import re
import os
import shutil
import sys
import codecs
from datetime import datetime, timedelta, timezone
import secrets
import string
import csv
from joblib import Parallel, delayed
from tqdm import tqdm
import subprocess
import filecmp 
import time
import random
import statistics
import pandas as pd
import networkx as nx
import zipfile

#-----------------------------------------------------------
# 


# def is_recursive( files, fun_name ):


def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def install_deps():
    def package( p ):
        os.system(f'sudo apt install {p} -y')
    for p in ['llvm','python3-pandas','python3-networkx']:
        package(p)

def zip_folder(folder_path, zip_filename):
    with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                file_path = os.path.join(root, file)
                zipf.write(file_path, os.path.relpath(file_path, folder_path))
        
#-----------------------------------------------------------

class Autograder:
    prob_path     = ''
    prob_files    = []
    students_path = ''
    student_files = []
    allowed_include = []
    disallowed_functions = ['cout','cerr','new ','append','alloc(','malloc(','free']
    
    test_repeat = 3
    timeout = 1
    parallel=-1
    exam= ""
    problem= ""
    
    tests_path    = ''
    tests         = []
    tmp_path      = ""
    students = []
    grading_files = []

    #-----------------------------------------------------------


    # constructor function    
    def __init__(self,
                 exam,
                 problem,
                 prob_path,
                 prob_files,     
                 students_path,        
                 students,
                 student_files,        
                 allowed_include,      
                 disallowed_functions, 
                 timeout,              
                 tests_path,           
                 tests
                 ):
        self.exam                 = exam             
        self.problem              = problem            
        self.prob_path            = prob_path             
        self.prob_files           = prob_files            
        self.students_path        = students_path        
        self.students             = students             
        self.student_files        = student_files        
        self.allowed_include      = allowed_include      
        self.disallowed_functions = disallowed_functions 
        self.timeout              = timeout              
        self.tests_path           = tests_path           
        self.tests                = tests
        self.tmp_path              = '/tmp/ds'
        os.system(f'mkdir -p {self.tmp_path}')
        
    # students = students #[1:10]
    # action  = sys.argv[1]

    #----------------------------------
    # Compile
    #----------------------------------

    def cleanup_student_code( self, student, rm_includes = True ):
        spath = os.path.abspath(self.students_path)
        new_sfiles = []
        for f in self.student_files:
            if not os.path.isfile( f'{spath}/{student}/{f}' ):
                continue
            text = open( f'{spath}/{student}/{f}', 'r' ).read()
            text = comment_remover(text)
            # --------------------------
            # Remove bad include files
            # --------------------------
            lines = text.split('\n')
            clines = []
            for line in lines:
                if '#include' in line:
                    found = True
                    for include in self.allowed_include:
                        if include in line:
                            found = False
                            break
                    if found and rm_includes:
                        line = '//'+line
                clines.append(line)
            text = "\n".join(clines)
            # --------------
            # save the files
            # --------------
            open( f'{self.tmp_path}/{student}.{f}', 'w' ).write(text)
            new_sfiles.append( f'{self.tmp_path}/{student}.{f}' )
        return new_sfiles
    
    def source_files(self,student, rm_includes = True):
        ppath = os.path.abspath(self.prob_path)
        spath = os.path.abspath(self.students_path)    
        files = [ f"{ppath}/{f}" for f in self.prob_files]
        sfiles = self.cleanup_student_code( student, rm_includes )
        return files + sfiles

    def source_paths(self):
        ppath = os.path.abspath(self.prob_path)
        return [ppath]
        # spath = os.path.abspath(self.students_path)
        # tpath = os.path.abspath(self.tmp_path)
        # return [ppath,spath,tpath]

    def compile_internal(self,student, show_error=False, rm_includes= True, verbose=False):
        # ---------------------
        extra_inclues = ""
        if not rm_includes: extra_inclues = "-extra-includes"
        # ---------------------
        includes  = " ".join( [ f'-I{p}' for p in self.source_paths()] )
        includes += " -I"+os.path.abspath(self.students_path)+f"/{student}"        
        try:
            files = self.source_files(student, rm_includes)
        except Exception as e:
            print( student, "Failed to process files: ", '{}!'.format(e) )
            return
        files = " ".join(files)
        dump_file = f"2> {self.tmp_path}/{student}.compile.txt{extra_inclues}"
        if show_error:
            dump_file = ""
        cmd = f"g++ -Wall -std=c++2a -o {self.tmp_path}/{student} {includes} {files} {dump_file}"
        if verbose == True:
            print(cmd)
        else:
            if extra_inclues:
                print( f"Compiling {student} with extra inclues!")
            else:
                print( f"Compiling {student}")
        os.system(cmd)

    def compile(self,student, show_error=False, verbose = False):
        self.compile_internal(student, show_error, verbose = verbose )
        if not self.check_compile_ok(student):
            self.compile_internal(student, show_error = show_error, rm_includes = False, verbose = verbose)

    def compile_all(self, show_error=False, verbose=False):
        Parallel(n_jobs=-1)( delayed(self.compile)(student, show_error=show_error, verbose=verbose) for student in tqdm(self.students) )

    #----------------------------------
    # Compile check
    #----------------------------------

    def check_compile_ok(self,student):
        compile_file = f"{self.tmp_path}/{student}.compile.txt"
        if not os.path.isfile(compile_file):
            return False
        f = open(compile_file, 'rb')
        s = f.read()
        if b'error' in s:
            return False
        else:
            return True

    def check_compile_with_extra_includes_ok(self,student):
        compile_file = f"{self.tmp_path}/{student}.compile.txt-extra-includes"
        if not os.path.isfile(compile_file):
            return False
        f = open(compile_file, 'rb')
        s = f.read()
        if b'error' in s:
            return False
        else:
            return True

    def report_compile_error(self):
        errors = {}
        for student in self.students:
            if self.check_compile_ok(student):
                errors[student] = "PASS"
            elif self.check_compile_with_extra_includes_ok(student):
                errors[student] = "PASS-WITH-INCLUDES"                
            else:
                errors[student] = "FAIL"
        df = pd.DataFrame(errors.items())
        df = df.rename(columns = { 0: 'Roll No', 1: 'Compile Success' })
        return df

    #----------------------------------
    # Policy checks
    #----------------------------------

    def include_check(self,student,lines):
        lines = [line for line in lines if "#include" in line]
        for line in lines:
            found = False
            for include in self.allowed_include:
                if include in line:
                    found = True
            if not found:
                with open(f'{self.tmp_path}/{student}.policy.txt', 'a') as f:
                    f.write(f'Dis-allowed includes: {line}\n')

    def disallowed_functions_check(self,student,lines):
        for line in lines:
            line = line.split('//')[0]
            for f in self.disallowed_functions:
                if f in line:
                    with open(f'{self.tmp_path}/{student}.policy.txt', 'a') as f:
                        f.write(f'Dis-allowed functions:{line}\n')
                        
    def recursion_check(self,student,sfile):
        # sfile = f"{self.tmp_path}/{student}.{f}"
        includes = " ".join( [ f'-I{p}' for p in self.source_paths()] )
        cmd = f'clang++ -S -emit-llvm {includes} {sfile} -o - 2> /dev/null | opt -passes=dot-callgraph  > /dev/null 2>&1'
        # print(cmd)
        os.system(cmd)
        os.system(f'mv \\<stdin\\>.callgraph.dot {sfile}.cfg.dot')
        text = open( f'{sfile}.cfg.dot', 'r' ).read()
        p = re.compile(r'Node0x(.*) -> Node0x(.*);')
        out = re.findall( p, text)
        G = nx.DiGraph(out)
        # if len(nx.simple_cycles(G)) > 0:
        #     print(student)
        for cycle in nx.simple_cycles(G):
            # print(student)
            lines = open( sfile, 'r' ).readlines()
            # for line in lines:
            #     print(line)
            with open(f'{self.tmp_path}/{student}.policy.txt', 'a') as f:
                f.write(f'Recursion found!\n')
            break
            # print(cycle)


        
    def policy_checks(self,student):
        policy_file = f"{self.tmp_path}/{student}.policy.txt"
        os.system( f'rm -rf {policy_file}' )
        spath = os.path.abspath(self.students_path)
        for f in self.student_files:
            sfile = f"{self.tmp_path}/{student}.{f}"
            if os.path.isfile(sfile):
                text = open( sfile, 'r' ).read()
                text = comment_remover(text)
                lines = text.split('\n')
                self.include_check(student, lines)
                self.disallowed_functions_check(student, lines)
                # self.recursion_check(student,sfile)

    def check_policy(self):
        for student in self.students:
            self.policy_checks(student)

    def report_policy_error(self):
        errors = {}
        for student in self.students:
            if os.path.isfile( f'{self.tmp_path}/{student}.policy.txt' ):
                errors[student] = True
                print('-------------------------')
                print( f'Policy error: {student}' )
                os.system( f'cat {self.tmp_path}/{student}.policy.txt' )
            else:
                errors[student] = False
        df = pd.DataFrame(errors.items())
        df = df.rename(columns = { 0: 'Roll No', 1: 'Policy Error' })
        return df

    #----------------------------------
    # Run
    #----------------------------------

    def run_test( self, student, test, timeout, std_interface=False ):
        # ------------------------------------
        #  Input output interface
        #    -- input folder where input file(s) are located 
        #    -- output file
        # ------------------------------------
        if std_interface:
            cmd = [f'{self.tmp_path}/{student}']
            print(" ".join(cmd), f'< {self.tests_path}/{test}',f'> {self.tmp_path}/{student}.{test}.output.txt')
        else:
            cmd = [f'{self.tmp_path}/{student}',f'{self.tests_path}/{test}',f'{self.tmp_path}/{student}.{test}.output.txt', f'2> /dev/null']
            print(" ".join(cmd))
        compile_ok = (self.check_compile_ok(student) or self.check_compile_with_extra_includes_ok(student))
        if os.path.isfile(f'{self.tmp_path}/{student}') and compile_ok:
            wrong = ""
            try:
                input_text = open(f'{self.tests_path}/{test}/input.txt', 'rb').read()
                start_time  = time.time()
                stdout_file = f'{self.tmp_path}/{student}.{test}.stdout.txt'
                out = subprocess.check_output( cmd,
                                         input=input_text,
                                         stderr=open('/dev/null','w'),
                                         timeout=timeout )
                tt = time.time() - start_time
                with open(f'{self.tmp_path}/{student}.{test}.stdout.txt', 'w') as f:
                    f.write(out.decode("utf-8"))
                with open(f'{self.tmp_path}/{student}.{test}.time.txt', 'a') as f:
                    f.write(str(tt)+'\n')
                if std_interface:
                    with open(f'{self.tmp_path}/{student}.{test}.output.txt', 'w') as f:
                        f.write(out.decode("utf-8"))
            except subprocess.CalledProcessError as exc:
                wrong = "segfault"
            except subprocess.TimeoutExpired as exc:
                wrong = "timeout"
            except Exception as e:
                wrong = f"{e}"
            if wrong:
                print(f'{student} {test} {wrong}')
                with open(f'{self.tmp_path}/{student}.{test}.error.txt', 'a') as f:
                    f.write(wrong+'\n')

    # TODO via shell
    # def create_tasks( self, tasks ):
    #     f = open(f'{self.tmp_path}/tasks.txt', 'w')
    #     for (student,test,timeout) in tasks:
    #         if os.path.isfile(f'{self.tmp_path}/{student}') and self.check_compile_ok(student):
    #             cmd = [f'{self.tmp_path}/{student}',f'{self.tests_path}/{test}',f'{self.tmp_path}/{student}.{test}.output.txt', f'1> {self.tmp_path}/{student}.{test}.stdout.txt', f'2> {self.tmp_path}/{student}.{test}.stderr.txt']
    #             f.write(" ".join(cmd)+'\n')
    #     f.close()
         

    def run_tests(self, std_interface = False):
        tasks = []
        for test in self.tests:
            for student in self.students:   
                os.system( f'rm -rf {self.tmp_path}/{student}.{test}.time.txt' )
                os.system( f'rm -rf {self.tmp_path}/{student}.{test}.error.txt' )
        for test in self.tests:
            for student in self.students:
                for i in range(0,self.test_repeat):
                    tasks.append( (student, test, self.timeout) )
        random.shuffle(tasks)
        # Via python concurrency
        def runner( task ):
            self.run_test( task[0], task[1], task[2], std_interface=std_interface )
        Parallel(n_jobs=self.parallel)( delayed(runner)( task ) for task in tasks )


    #----------------------------------
    # Run check
    #----------------------------------

    def report_runtime_error(self):
        all_errors = pd.DataFrame( columns = ['Roll No'] )
        for test in self.tests:
            errors = {}
            for student in self.students:
                if os.path.isfile( f'{self.tmp_path}/{student}.{test}.error.txt' ):
                    errors[student] = True
                    # print( f'Runtime error: {student} {test}' )
                else:
                    errors[student] = False                    
            df = pd.DataFrame(errors.items())
            df = df.rename(columns = { 0: 'Roll No', 1: test })
            all_errors = pd.merge( all_errors, df, on= ['Roll No'], how='outer' )
        return all_errors

    def test_ok(self,student,test):
        output   = os.path.abspath(f"{self.tmp_path}/{student}.{test}.output.txt")
        expected = os.path.abspath(f"{self.tests_path}/{test}/output.txt")
        # print(output)
        # print(expected)
        if os.path.isfile(output) and filecmp.cmp(output,expected):
            return True
        return False
    
    def test_match_count(self, student, test):
        output   = os.path.abspath(f"{self.tmp_path}/{student}.{test}.output.txt")
        expected = os.path.abspath(f"{self.tests_path}/{test}/output.txt")
        expected = open( expected, 'r' ).readlines()
        score = 0
        if os.path.isfile(output):
            output = open( output, 'r' ).readlines()
            for i,e_output in enumerate(expected):
                if i < len(output):
                    if( output[i] == e_output ):
                        score = score + 1
        return score
    
    # def tests_ok_count(self,student):
    #     cnt = 0
    #     for test in self.tests:
    #         if self.test_ok( student, test ):
    #             cnt = cnt + 1
    #     return cnt

    
    def print_fail(self,student):
        for test in self.tests:
            output   = f"{self.tmp_path}/{student}.{test}.output.txt"
            expected = f"{self.tests_path}/{test}/output.txt"
            if os.path.isfile(output) and not filecmp.cmp(output,expected):
                os.system(f'diff {expected} {output} | head -10')

    def get_time(self,student,test):
        tfile   = f"{self.tmp_path}/{student}.{test}.time.txt"
        if os.path.isfile(tfile):
            times = [float(t) for t in open( tfile, 'r' ).readlines()]
            return statistics.mean(times)
        else:
            return float(self.timeout)

    def get_stdout(self,student,test):
        if not self.test_ok(student,test):
            return None
        tfile   = f"{self.tmp_path}/{student}.{test}.stdout.txt"
        if os.path.isfile(tfile):
            stdout = open( tfile, 'r' ).read()
            return stdout
        else:
            return None

    def report_match_count(self):
        all_results = pd.DataFrame( columns = ['Roll No'] )
        for test in self.tests:
            counts = {}
            for student in self.students:
                counts[student] = self.test_match_count(student,test)
            df = pd.DataFrame(counts.items())
            df = df.rename(columns = { 0: 'Roll No', 1: test })
            all_results = pd.merge( all_results, df, on= ['Roll No'], how='outer' )
        return all_results

    def report_result(self):
        all_results = pd.DataFrame( columns = ['Roll No'] )
        for test in self.tests:
            counts = {}
            for student in self.students:
                counts[student] = self.test_ok(student,test)
            df = pd.DataFrame(counts.items())
            df = df.rename(columns = { 0: 'Roll No', 1: test })
            all_results = pd.merge( all_results, df, on= ['Roll No'], how='outer' )
        return all_results

    def report_time(self):
        all_timings = pd.DataFrame(columns = ['Roll No'])
        for test in self.tests:
            scores = {}
            for student in self.students:
                scores[student] = self.get_time(student,test)
            scores = dict(sorted(scores.items(), key=lambda item: item[1]))
            df = pd.DataFrame(scores.items())
            df = df.rename(columns = { 0: 'Roll No', 1: test+'-time' })
            all_timings = pd.merge( all_timings, df, on= ['Roll No'], how='outer' )
        return all_timings

    def report_stdouts(self):
        all_results = pd.DataFrame( columns = ['Roll No'] )
        for test in self.tests:
            stdouts = {}
            for student in self.students:
                stdouts[student] = self.get_stdout(student,test)
            df = pd.DataFrame(stdouts.items())
            df = df.rename(columns = { 0: 'Roll No', 1: test })
            all_results = pd.merge( all_results, df, on= ['Roll No'], how='outer' )
        return all_results


    def create_student_package(self,student):
        folder = f'{self.tmp_path}/{student}-grader'
        os.system(f'mkdir -p {folder}')
        os.system(f'mkdir -p {folder}/tests')
        os.system(f'mkdir -p {folder}/students')
        os.system(f'cp -r {self.prob_path} {folder}/harness')
        os.system(f'cp -r {self.students_path}/{student} {folder}/students/')
        for t in self.tests:
            os.system(f'cp -r {self.tests_path}/{t} {folder}/tests/')
        for f in self.grading_files:
            fname = os.path.basename(f)
            os.system(f'cp {f} {folder}/')
            os.system(f"sed -i 's|.*{self.package_replace_sequence}.*|students_path = \"./students/\"\\nprob_path = \"./harness/\"\\ntests_path = \"./tests/\"\\n|g' {folder}/{fname}")
        zip_folder(folder, folder+'.zip')
        print(folder+'.zip')
            
    def create_packages(self):
        Parallel(n_jobs=self.parallel)( delayed(self.create_student_package)( s ) for s in self.students )

    def send_emails(self):
        # print(" Hard blocked!")
        # exit()
        import bulk_email
        send = False
        for student in self.students:
            # if student == '23B0948':
            #     send = True
            # if send == False: continue
            file_path =  f"{self.tmp_path}/{student}-grader.zip"
            student_email = student + '@iitb.ac.in'
            if os.path.exists(file_path):
                print(f"Sending email to {student_email} for roll number: {student}")
                bulk_email.send_email( student, student_email, self.exam, self.problem, file_path)
            else:
                print(f"File not found for roll number: {student}")
            time.sleep(5)
            
    def move_tests(self,test_store, prefix):
        inputs = test_store+'/inputs'
        outputs = test_store+'/outputs'
        onlyfiles = [f for f in os.listdir(inputs) if os.path.isfile(os.path.join(inputs, f))]
        i = 0
        for test in onlyfiles:
            os.system( f'mkdir -p ./tests/{prefix}{i}')
            os.system( f'cp {inputs}/{test} ./tests/{prefix}{i}/input.txt' )
            os.system( f'cp {outputs}/{test} ./tests/{prefix}{i}/output.txt' )
            i = i + 1
