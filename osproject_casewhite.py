import numpy as numpy
import os
import pandas as pd
#!pip3 install the fuzz
from fuzzywuzzy import fuzz 
from fuzzywuzzy import process
import sys
import shutil
import subprocess #to run c files

faq_data = pd.read_csv('/home/sagar24/OS_project/dataset.csv')
cwd = os.getcwd()

def ls():
    #print('\n')
    cmd='ls'
    os.system(cmd)

def pwd():
    #cwd = os.getcwd()
    #print('\n')
    print("The current working directory is : {0}".format(cwd))

def cd():
    '''
    function to navigate through directories
    '''
    global cwd
    cwd1=cwd+"/"
    while(True):
        #print(os.listdir(cwd))
        input1 = input("Enter the directory u want to go to, or enter back, else enter exit:\n")
        if(input1 == "exit"):
            #print("OK")
            return
        elif(input1 == "back"):
            n=len(cwd)
            cwd=cwd[0:n-1]
            l_o_i = cwd.rindex("/") 
            cwd = cwd[0:l_o_i]
            cwd=cwd+"/"
            print(cwd)
            continue
        cwd1=cwd1+input1+"/"
        cwd=cwd1
        print(os.listdir(cwd1))

def mkdir(name):
    '''
    function to make a new directory
    '''
    directory=name
    parent_dir=cwd+"/"
    path=os.path.join(parent_dir,directory)
    os.mkdir(path)

def rmdir():
    '''
    function to delete an existing directory / file
    '''
    #print('\n')
    mydir= input("Enter directory name: ")
    try:
        shutil.rmtree(mydir)
    except OSError as e:
        print("Error: %s - %s." % (e.filename, e.strerror))

def exec_cpu_sche():
    '''
    refer cpu_sche.cpp code for the same
    '''
    subprocess.call(["g++", "cpu_sche.cpp"]) 
    tmp=subprocess.call("./a.out") 
    

def open_sub():
    '''
    the function opens Sublime Text
    the go-to text editor used during labs
    '''
    cmd='subl'
    os.system(cmd)
'''
time to correct the find() function
'''
def find():
    for dpath, dnames, fnames in os.walk("."):
      for i, fname in enumerate([os.path.join(dpath, fname) for fname in fnames]):
        input1=input("Enter extension\n")
        if fname.endswith(input1):
            #os.rename(fname, os.path.join(dpath, "%04d.png" % i))
            print ("mv %s %s" % (fname, os.path.join(dpath, "%04d.png" % i)))

def compile():
    '''
    the function compiles code irrespective of the file extension
    the current code can compile C, C++ and Java
    '''
    #print('\n')
    input1=input("enter the name if file:\n")
    split_tup = os.path.splitext(input1)
    print(split_tup)
  
    # extract the file name and extension
    file_name = split_tup[0]
    file_extension = split_tup[1]
    
    if(file_extension==".c"):
        subprocess.call(["gcc", input1]) 
        input2=input("Do you want to run the file [Y/n]  ::  ")
        print("\n\n\n\n")
        if(input2=='Y'):
            tmp=subprocess.call("./a.out")

    elif(file_extension==".cpp"):
        subprocess.call(["g++", input1]) 
        input2=input("Do you want to run the file [Y/n]  ::  ")
        print("\n\n\n\n")
        if(input2=='Y'):
            tmp=subprocess.call("./a.out")


def GetAnswer():
    '''
    input1 takes input from user
    questions is a list of questions parsed from dataset.csv
    matched questions is a list of questions that are similar to input question
    '''
    input1 = input('>>')
    if(input1=="exit"):
        return -1
    questions = faq_data['question'].values.tolist()

    mathed_question, score = process.extractOne(input1, questions, scorer=fuzz.token_set_ratio) # use process.extract(.. limits = 3) to get multiple close matches

    if score > 50: # arbitrarily chosen 50 to exclude matches not relevant to the query
        matched_row = faq_data.loc[faq_data['question'] == mathed_question,]
        match = matched_row['question'].values[0]
        answer = matched_row['answers'].values[0]
        #print(answer.dtype)
        response = "Question: {} \n Answer: {} \n".format(match, answer)
        #print(response)
        if answer == 1:
            ls()
        if answer == 2:
            pwd()
        if answer == 3:
            cd()
        if answer == 4:
            input2=str(input("Enter the name for the new folder\n"))
            mkdir(input2)
        if answer == 5:
            rmdir()
        if answer == 6:
            exec_cpu_sche()
        if answer == 7:
            open_sub()
        if answer == 8:
            find()
        if answer == 9:
            compile()
    else:
        response = "Sorry I couldn't find anything relevant to your query, try specifying it in a better manner please!"
        print(response)


    # dispatcher.utter_message(response)
#ctrl kc and ctrl ku
while(True):
    a = GetAnswer()
    print('\n')
    if (a==-1):
        break;