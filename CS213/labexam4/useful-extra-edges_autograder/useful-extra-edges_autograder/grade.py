import os

STUDENT_FILENAME = "useful-extra-edges.cpp"
ORIGINAL_FILENAME = "useful-extra-edges_original.cpp"
TESTCASES_DIR = "testcases"

# Check if the file is in current directory or not.
ret = os.system(f"ls {STUDENT_FILENAME} > /dev/null 2>&1")
if ret != 0:
    print(f"File '{STUDENT_FILENAME}' not found in current directory.")
    exit(1)

print("File found.")

# Check if student attempted or not.
ret = os.system(f"diff -Bw {STUDENT_FILENAME} {ORIGINAL_FILENAME} > /dev/null 2>&1")
if ret == 0:
    print("Student did not attempt the question.")
    print("Total Marks: 0")
    exit(0)

print("You have attempted the question.")

# Check if only 1 #include or not.
with open(STUDENT_FILENAME, "r") as f:
    lines = f.readlines()
    count = 0
    for line in lines:
        if line.startswith("#include"):
            count += 1
    if count > 1:
        print("More than 1 #include found.")
        print("Total Marks: 0")
        exit(0)

# Check if file compiles or not.
ret = os.system(f"g++ -std=c++17 -o test {TESTCASES_DIR}/testcase_template.cpp main.cpp {STUDENT_FILENAME} > /dev/null 2>&1")
if ret != 0:
    print("File does not compile.")
    print("Total Marks: 0")
    exit(0)

print("File compiles.")
print("")
os.system("rm test")

# Checking testcases...
# 7 testcases, 1 mark first 7, last one 2 marks.
marks = 0
for i in range(1, 8):
    print(f"Grading testcase {i}...")
    os.system(f"g++ -std=c++17 -o testcase_{i}.out {TESTCASES_DIR}/testcase_{i}.cpp main.cpp {STUDENT_FILENAME} > /dev/null 2>&1")
    ret = os.system(f"timeout 5s ./testcase_{i}.out > output.txt")
    if ret != 0:
        print("Runtime Error/Timeout. Testcase failed.")
        print("Marks for this testcase: 0")
        print("")
        continue
    ret = os.system(f"diff -Bw output.txt {TESTCASES_DIR}/output_testcase_{i}.txt > /dev/null 2>&1")
    if ret != 0:
        print("Wrong Answer. Testcase failed.")
        print("Marks for this testcase: 0")
        print("")
        continue
    print("Testcase passed.")
    if i == 7:
        print("Marks for this testcase: 2")
        marks += 2
    else:
        print("Marks for this testcase: 1")
        marks += 1
    print("")

os.system("rm testcase_*.out output.txt")

print(f"Total Marks: {marks}")