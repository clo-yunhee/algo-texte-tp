#!/usr/bin/python3

import subprocess
import matplotlib.pyplot as plt

print('--- Benchmarking Exact Word Search algorithms ---')

# *.alg [mots] [texte]

NB_ITER = 100

CARD = [2,4,20,70]
LENS = [4,5,6,7,8,9,10,15,20,30,40,50]


def time_command(command, *args):
    proc_args = ['/usr/bin/time', '-f', '%e', command, *args]
    try:
        output = subprocess.check_output(proc_args)
        return float(output.decode('UTF-8').rstrip())
    except subprocess.CalledProcessError as e:
        print('Error while timing: \n', e.output);
        return 0.0

def enumerate_algs(algbin_fmt='{}.alg'):
    pass

def enumerate_data_files(text_fmt='texte_{cd}',
                         words_fmt='mots_{cd}_lg{lg}'):
    data = {}
    for cd in CARD:
        data[cd] = data_cd = {}
        data_cd['text'] = text_fmt.format(cd=cd)
        data_cd['words'] = data_wd = {}
        for lg in LENS:
            data_wd[lg] = words_fmt.format(cd=cd, lg=lg)
    return data

def time_for(files):
    x = []
    y = []

    text = files['text']
    words = files['words']

    for (lg, word) in words:
        time_total = 0.0
        for it in range(NB_ITER):
            time_total += time_command("")

    return (x, y)


data = enumerate_data_files()
times = [time_for(data[cd]) for cd in CARD]


