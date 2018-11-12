#!/usr/bin/python3

import os, argparse, subprocess

def define_constants(**kwargs):
    global NB_ITER, CARD, LENGTHS

    NB_ITER = kwargs['nb_iter']
    CARD = kwargs['card']
    LENGTHS = kwargs['lengths']

def ensure_dir_exists(dirname):
    if os.path.isdir(dirname):
        return
    elif not os.path.exists(dirname) and not os.path.islink(dirname):
        os.mkdir(dirname)
    else:
        raise IOError('Directory could not be created')

def time_command(command, *args):
    proc_args = ['/usr/bin/time', '-f', '%e', command, *args]
    try:
        proc = subprocess.Popen(proc_args, \
                    stdout=subprocess.PIPE, \
                    stderr=subprocess.PIPE)
        output = proc.communicate()[1]
        return float(output.decode('UTF-8').rstrip())
    except subprocess.CalledProcessError as e:
        print('Error while timing: \n', e.output);
        return 0.0

def enumerate_algs(algbin_fmt=r'^(.*)\.alg$'):
    from re import compile

    algbin_pat = compile(algbin_fmt)
    algs = []

    for file in os.listdir():
        match = algbin_pat.match(file)
        if match is not None:
            algs.append({
                'name': match.group(1),
                'file': './' + file
            })

    return algs


def enumerate_data_files(text_fmt='data/texte_{cd}',
                         words_fmt='data/mots_{cd}_lg{lg}'):
    data = {}
    for cd in CARD:
        data[cd] = data_cd = {}
        data_cd['text'] = text_fmt.format(cd=cd)
        data_cd['words'] = data_wd = {}
        for lg in LENGTHS:
            data_wd[lg] = words_fmt.format(cd=cd, lg=lg)
    return data

def time_alg_card(alg, card_files):
    x = []
    y = []

    alg_file = alg['file']

    text = card_files['text']
    words = card_files['words']

    print('     + Word length: ', end='')

    for (lg, word) in words.items():
        time_total = 0.0
        print('...', end='', flush=True)
        for it in range(NB_ITER):
            time_total += time_command(alg_file, word, text, '-q')
        time_total /= NB_ITER
        time_total = round(time_total, 5)

        print('\b\b\b', lg, ', ', sep='', end='', flush=True)

        x.append(lg)
        y.append(time_total)

    print('\b\b ')

    return (x, y)

def time_alg(alg, files):
    alg_times = {}

    for (card, card_files) in files.items():
        print('   - Character count:', card)

        alg_times[card] = time_alg_card(alg, card_files)

    return alg_times

def timeall(algs, data):
    times = {}

    for alg in algs:
        alg_name = alg['name']
        print(' * Algorithm:', alg_name)

        times[alg_name] = time_alg(alg, data)

    return times

def save_times(times, subdir='benchmarks', filename='benchmark_results.py'):
    ensure_dir_exists(subdir)
    with open('{}/{}'.format(subdir, filename), mode='wt') as f:
        f.write(str(times))
        f.write('\n')

def load_times(subdir='benchmarks', filename='benchmark_results.py'):
    ensure_dir_exists(subdir)
    with open('{}/{}'.format(subdir, filename), mode='rt') as f:
        code = compile(f.read(), filename, 'eval')
        return eval(code)

def plot_card(plt, algs, card, times):
    fig = plt.figure()

    plt.xlabel('Word length')
    plt.xticks(LENGTHS)

    plt.ylabel('Time (seconds)')

    for alg in algs:
        alg_name = alg['name']
        alg_times = times[alg_name][card]

        plt.plot(alg_times[0], alg_times[1], label=alg_name)

    plt.legend(title='Algorithms', title_fontsize=12)

    plt.suptitle('card(A) = {}'.format(card))

    return fig

def run_benchmarks(use_saved_results=False,
                   save_results=False,
                   subdir='benchmarks'):
    print(' ==#-*-#== Exact Word Search benchmark ==#-*-#==\n')

    algs = enumerate_algs()

    if not use_saved_results:
        print('-=- Timing algorithms run times... -=-')
        data = enumerate_data_files()
        times = timeall(algs, data)
        print('OK.\n')
        if save_results:
            print('-=- Saving results to file... -=-')
            save_times(times)
            print('OK.\n')
    else:
        print('-=- Loading results from file... -=-')
        times = load_times()
        print('OK.\n')

    print('-=- Plotting benchmark results... -=-')

    import matplotlib.pyplot as plt

    ensure_dir_exists(subdir)
    for card in CARD:
        fig = plot_card(plt, algs, card, times)
        filename = '{}/benchmark_{}.png'.format(subdir, card)
        fig.savefig(filename, format='png')
        print(' * Character count:', card)

    print('OK.\n')

    print(' === Benchmarks finished. ===')

def main():
    parser = argparse.ArgumentParser(
            description='Run and plot benchmarks on different exact word search algorithms')

    parser.add_argument('-u', '--use-saved',
            help='load precomputed benchmark results from disk',
            action='store_true')

    parser.add_argument('-s', '--save',
            help='save computed benchmark results to disk (ignored if --use-saved is also specified)',
            action='store_true')

    parser.add_argument('-o', '--out-dir', type=str,
            help='change the directory in which results and figures will be produced (default: \'benchmarks\')',
            metavar='outdir',
            nargs='?', default='benchmarks')

    parser.add_argument('-n', '--iter', type=int,
            help='execute each combination N times (default: 10)',
            metavar='<iter>',
            default=10)

    parser.add_argument('--counts', type=int,
            help='list of alphabet sizes to benchmark (default: [2,4,20,70]',
            metavar='count',
            nargs='*', default=[2,4,20,70])

    parser.add_argument('--lengths', type=int,
            help='list of word lengths to benchmark (default: [4..10,15,20..50]',
            metavar='length',
            nargs='*', default=[4,5,6,7,8,9,10,15,20,30,40,50])

    args = parser.parse_args()

    define_constants(
            nb_iter=args.iter,
            card=args.counts,
            lengths=args.lengths)

    run_benchmarks(
            use_saved_results=args.use_saved,
            save_results=args.save,
            subdir=args.out_dir)


main()
