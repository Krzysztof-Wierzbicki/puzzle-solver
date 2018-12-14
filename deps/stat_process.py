import os
import json

algorithms = ['bfs', 'dfs', 'astr']
parameters = {'bfs': ['rdul', 'rdlu', 'drul', 'drul', 'ludr', 'lurd', 'uldr', 'ulrd'], 'dfs': ['rdul', 'rdlu', 'drul', 'drul', 'ludr', 'lurd', 'uldr', 'ulrd'], 'astr': ['manh', 'hamm', 'mdlc']}

master = {}

for level in [1, 2, 3, 4, 5, 6, 7]:
    dlvl = {}
    print('Processing {}...'.format(level))
    
    for alg in algorithms:
        dalg = {}
        print('  Processing {}...'.format(alg))
            
        for par in parameters[alg]:
            print('    Processing {}...'.format(par))
            length = 0
            visited = 0
            processed = 0
            maxDepth = 0
            duration = 0.
            failed = 0
            count = 0

            for root, dirs, files in os.walk('.'):
                for name in files:
                    if '4x4_0{}_'.format(level) in name and '{}_{}_stats.txt'.format(alg, par) in name:
                        count += 1
                        with open(name, 'r') as f:
                            l = int(f.readline())
                            if l == -1:
                                failed += 1
                                continue
                            length += l
                            visited += int(f.readline())
                            processed += int(f.readline())
                            maxDepth += int(f.readline())
                            duration += float(f.readline())
            if count == 0:
                print('No stats for {} {} {}!'.format(level, alg, par))
                continue
                    
            length /= count
            visited /= count
            processed /= count
            maxDepth /= count
            duration /= count
            failed /= count
            
            dalg[par] = {'length': length, 'visited': visited, 'processed': processed, 'maxDepth': maxDepth, 'duration': duration, 'failed': failed, 'count': count}
        dlvl[alg] = dalg.copy()
    master['{}'.format(level)] = dlvl.copy() 
           
with open('summary.json', 'w') as f:
    f.write(json.dumps(master))

