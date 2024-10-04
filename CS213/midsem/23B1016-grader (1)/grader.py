#!/usr/bin/python3

import sys
# caution: path[0] is reserved for script path (or '' in REPL)

#---------------------------
# Paths
#---------------------------
sys.path.insert( 1,    '../../../utils' )
students_path        = '../../students/'
prob_path            = './harness/'
tests_path           = './tests'

students_path = "./students/"
prob_path = "./harness/"
tests_path = "./tests/"


import autograder
import pandas as pd
import numpy as np
import os
import copy

pd.set_option('display.max_rows', 200)


#------------------------------
# student lists
#------------------------------

students             = [ s for s in os.listdir(students_path) if os.path.isdir(students_path+'/'+s) ]

#------------------------------
# Setup for problem
#------------------------------
prob_files           = ['main.cpp','bst.h','rdtsc.h']
student_files        = ['kth.cpp']
allowed_include      = ['bst.h']
disallowed_functions = [#'cout','cerr',
                        'new ','append','alloc(','malloc(','free','delete ','[']

#------------------------------
# test cases
#------------------------------

tests    = ['test0','test1','test2','test3','test4',
            'small-10k', 'small-100k', 'small-1m' ]


#---------------------------------
# Allocate auto-grader
#--------------------------------
base_grader = autograder.Autograder(
    prob_path            = prob_path, 
    prob_files           = prob_files, 
    students_path        = students_path, 
    students             = students,
    student_files        = student_files, 
    allowed_include      = allowed_include, 
    disallowed_functions = disallowed_functions,
    tests_path           = tests_path,
    timeout              = 40,
    tests                = tests 
)
base_grader.test_repeat = 1

# long_grader = copy.copy( base_grader )
# long_grader.tests = largek_tests
# long_grader.timeout = 40


if len(sys.argv) < 2:
    print('Apply actions: compile, policy, run, results, grade, rollno')
    exit()

act  = sys.argv[1]


if len(sys.argv) == 3:
    rollno  = sys.argv[2]
    for f in student_files:
        f = f'../../students/{rollno}/{f}'
        if os.path.isfile(f):
            # os.system( f'cat {f}' )
            pass
    base_grader.students = [rollno]
    


# ---------------------
# Actions of auto-grader
# --------------------
if act in ['compile','policy','run','results','grade','package']:
    #-------------------------
    # Policy check
    #-------------------------

    if act in ['policy' ]: base_grader.check_policy()
    if act in ['compile']: base_grader.compile_all ()

    #-------------------------
    # Run submissions
    #-------------------------
    if act in ['run']    : base_grader.run_tests()

    #-------------------------
    # Merge results
    #-------------------------
    if act in ['results']:
        ce      = base_grader.report_compile_error()
        pe      = base_grader.report_policy_error()
        base    = base_grader.report_match_count ()
        sbase = base_grader.report_stdouts()
        sbase['small-10k'] = pd.to_numeric(sbase['small-10k'])
        sbase['test4'] = pd.to_numeric(sbase['test4'])
        rename = {}
        for test in base_grader.tests: rename[test] = test+'-clocks'
        sbase.rename( columns = rename, inplace = True )

        full = pd.merge(   ce, pe,      on=['Roll No'], how='outer' )
        full = pd.merge( full, base,      on=['Roll No'], how='outer' )
        full = pd.merge( full, sbase,      on=['Roll No'], how='outer' )
        full.sort_values(by=['small-10k-clocks','test4-clocks'],inplace=True)
        full.to_csv( 'results.csv', index=False )
        # full[full['Policy Error'] == True]['Roll No'].to_csv('~/tmp/bad1.csv')
    #-----------------------------------------------
    # Assign grade
    #-----------------------------------------------
    if act in ['grade']:
        full = pd.read_csv( 'results.csv')
        # exit()
        #-------------------------------
        # Check basic correctness
        #  -1 for failing zero and 1 node
        #   2 for 4 or more correct answers for trees with nodes 2, 3, and 4
        #  +1 for all correct answers fore for the trees
        #-------------------------------        
        full['base01' ] = np.where( ( (full['test0'] == 2) & (full['test1'] == 2) ), 0, -1)
        full['base234'] = full[['test2','test3','test4']].sum(axis=1)
        full['base234'] = np.where( (full['base234'] == 6 ), 1, 0 ) + np.where( (full['base234'] > 3 ), 2, 0 )
        full['base'] = (full['base01']+full['base234']).clip(0, None)

        #--------------------------------------------
        # Check if performance is O(kh) = O(k log n)
        #  We measure (run time of findKthSmallest)/k
        #  this is the average time to go from a node to
        #  its successor, which should be small and
        #  must grow log n.
        #-------------------------------------------
        
        #-------------------------------
        #  -- check 10k nodes tree works with small k (1 mark)
        #-------------------------------
        full['long'] = np.where( (full['small-10k-clocks'] > 0 ), 1, 0 )
        
        #--------------------------------------------------------------
        #  -- check 10k nodes indeed had reasonable performance (1 mark)
        #--------------------------------------------------------------
        full['long'] = full['long']+np.where( (full['small-10k-clocks'] < 1000 ), 1, 0 )


        #---------------------------------------------------------------------------
        # Check 10k,100k,1m node trees have similar performance for small k (1 mark)
        #---------------------------------------------------------------------------
        for test in ['small-10k','small-100k','small-1m']:
            full[test+'-fast'] = np.where( ((full[test] == 2) & (full[test+'-clocks'] < 100) ), True, False )
        full['fast-runs'] = full[['small-10k-fast','small-100k-fast','small-1m-fast']].sum(axis=1)
        full['small'] = full[['small-10k','small-100k','small-1m']].sum(axis=1)
        full['fast'] = np.where( ((full['fast-runs'] > 0) & (full['small'] == 6)), True, False )
        full['long'] = full['long']+full['fast']

        full['total'] = full['base']+full['long']

        #-------------------------------
        # Apply policy penalty
        #-------------------------------        
        full['total'] = full['total']+np.where( ((full['total'] > 3) & (full['Policy Error'])), -1, 0 )

        full['total'] = full['total']+np.where( ((full['total'] > 0) & (full['Compile Success'] == 'PASS-WITH-INCLUDES')), -1, 0 )

        print(full[['Roll No','test4-clocks','small-10k-clocks','small-100k-clocks','small-1m-clocks','base','long','total','Compile Success']])
        counts = full['total'].value_counts().reindex([0, 1, 2, 3, 4, 5, 6], fill_value=0)
        print(counts)
        print(full['total'].mean())
        full.to_csv( 'results_cal.csv', index=False)

    #-----------------------------------------------
    # create package
    #-----------------------------------------------
    if act in ['package']:
        base_grader.grading_files = ['./grader.py','../../../utils/autograder.py']
        base_grader.package_replace_sequence = auto_remove
        base_grader.create_packages()
        
    # if act in ['email']:
    #     #-------------------------------
    #     # Send emails to the students
    #     #-------------------------------        

    #     STUDENTS_DIR = './students/'

    #     student_list = pd.read_csv('student_list.csv')
    #     students_id = list(student_list['Roll'])
    #     print(students_id)
    #     zip_files = os.listdir('students')

    #     def zip_folder(folder_path, zip_filename):
    #         with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
    #             for root, dirs, files in os.walk(folder_path):
    #                 for file in files:
    #                     file_path = os.path.join(root, file)
    #                     zipf.write(file_path, os.path.relpath(file_path, folder_path))

    #     for stu_id in students_id:
    #         stu_id = stu_id.upper()
    #         folder = './students/'+stu_id
    #         zip_filename = './students/'+stu_id+'.zip'
    #         zip_folder(folder, zip_filename)
    #         print(f"Zipped folder {folder} to {zip_filename}")
