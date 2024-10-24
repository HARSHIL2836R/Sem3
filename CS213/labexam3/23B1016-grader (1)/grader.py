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
import matplotlib.pyplot as plt

pd.set_option('display.max_rows', 200)


#------------------------------
# student lists
#------------------------------

students             = [ s for s in os.listdir(students_path) if os.path.isdir(students_path+'/'+s) ]

#------------------------------
# Setup for problem
#------------------------------
exam                 = "Lab Exam03"
problem              = "max-fish"
prob_files           = ['main.cpp']
student_files        = ['fish.cpp']
allowed_include      = ['vector','queue']
disallowed_functions = [#'cout','cerr',
                        'new ','append','alloc(','malloc(','free','delete ' #,'['
                       ]

grades_file = "grade.csv"

#------------------------------
# test cases
#------------------------------

tests    = [
    'exam-tests-0',
    'exam-tests-2',
    'exam-tests-4',
    'exam-tests-5',
    'exam-tests-8',
    'large-100',
    'large-1k',
    'large-10k1k',
]

#---------------------------------
# Allocate auto-grader
#--------------------------------
base_grader = autograder.Autograder(
    exam                 = exam, 
    problem              = problem, 
    prob_path            = prob_path, 
    prob_files           = prob_files, 
    students             = students,
    students_path        = students_path, 
    student_files        = student_files, 
    tests_path           = tests_path,
    tests                = tests,
    allowed_include      = allowed_include, 
    disallowed_functions = disallowed_functions,
    timeout              = 40,
)
base_grader.test_repeat = 1

# base_grader.move_tests( './../../prob/max-fish/testcases/', 'exam-tests-' )
# exit()

# long_grader = copy.copy( base_grader )
# long_grader.tests = largek_tests
# long_grader.timeout = 40


if len(sys.argv) < 2:
    print('Usage ./grader.py {action} [rollno]')
    print('Actions: all, policy, compile, run, results, grade')
    print('Roll no is is optional')
    exit()

act  = sys.argv[1]


if len(sys.argv) == 3:
    rollno  = sys.argv[2]
    #----------------
    # Redirected 
    #----------------
    if rollno.isdigit():
        full = pd.read_csv( grades_file)
        rollno = full.iloc[int(rollno)]['Roll No']
    for f in student_files:
        f = f'../../students/{rollno}/{f}'
        if os.path.isfile(f):
            os.system( f'cat {f}' )
            pass
    base_grader.students = [rollno]
    


# ---------------------
# Actions of auto-grader
# --------------------
if act in ['compile','policy','run','results','grade','package','email','all']:
    #-------------------------
    # Policy check
    #-------------------------

    if act in ['policy' , 'all']: base_grader.check_policy()
    if act in ['compile', 'all']: base_grader.compile_all ()

    #-------------------------
    # Run submissions
    #-------------------------
    if act in ['run','all']    : base_grader.run_tests(std_interface = True)

    #-------------------------
    # Merge results
    #-------------------------
    if act in ['results','all']:
        ce      = base_grader.report_compile_error()
        pe      = base_grader.report_policy_error()
        base    = base_grader.report_result ()
        time    = base_grader.report_time ()
        full = pd.merge(   ce, pe,   on=['Roll No'], how='outer' )
        full = pd.merge( full, base, on=['Roll No'], how='outer' )
        full = pd.merge( full, time, on=['Roll No'], how='outer' )
        full.to_csv( 'results.csv', index=False )
        
        print(full)
    #-----------------------------------------------
    # Assign grade
    #-----------------------------------------------
    if act in ['grade','all']:
        full = pd.read_csv( 'results.csv' )

        full['total'] = full[tests].sum( axis = 1 )
        counts = full['total'].value_counts().reindex( [0,1,2,3,4,5,6,7,8], fill_value = 0 )
        print(counts)
        print(full['total'].mean())
        full.to_csv( grades_file, index=False )
        print(full[['Roll No','total']])

    #-----------------------------------------------
    # create package
    #-----------------------------------------------
    if act in ['package']:
        base_grader.grading_files = ['./grader.py','../../../utils/autograder.py']
        base_grader.package_replace_sequence = auto_remove
        base_grader.create_packages()
        
    if act in ['email']:
        base_grader.send_emails()

