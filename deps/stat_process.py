import os

algorithms = ['bfs', 'dfs', 'astr']
parameters = {'bfs': ['RDUL', 'RDLU', 'DRUL', 'DRLU', 'LUDR', 'LURD', 'ULDR', 'ULRD'], 'dfs': ['RDUL', 'RDLU', 'DRUL', 'DRLU', 'LUDR', 'LURD', 'ULDR', 'ULRD'], 'astr': ['manh', 'hamm', 'mdlc']}

csv = {'header': [], 'length': [], 'visited': [], 'processed': [], 'maxDepth': [], 'duration': [], 'count': []}

for alg in algorithms:
    alength = 0
    avisited = 0
    aprocessed = 0
    amaxDepth = 0
    aduration = 0.
    acount = 0
    
    for par in parameters[alg]:
        length = 0
        visited = 0
        processed = 0
        maxDepth = 0
        duration = 0.
        
        count = 0

        for root, dirs, files in os.walk('.'):
            for name in files:
                if '4x4' in name and 'stats' in name and par in name and alg in name:
                    count += 1
                    with open(name, 'r') as f:
                        length += int(f.readline())
                        visited += int(f.readline())
                        processed += int(f.readline())
                        maxDepth += int(f.readline())
                        duration += float(f.readline())
        if count == 0:
            continue
                
        length /= count
        visited /= count
        processed /= count
        maxDepth /= count
        duration /= count
        
        alength += length
        avisited += visited
        aprocessed += processed
        amaxDepth += maxDepth
        aduration += duration
        acount += 1

        csv['header'].append('{}_{}'.format(alg, par)) 
        csv['length'].append(length) 
        csv['visited'].append(visited) 
        csv['processed'].append(processed) 
        csv['maxDepth'].append(maxDepth) 
        csv['duration'].append(duration) 
        
    if acount != 0:
        alength /= acount
        avisited /= acount
        aprocessed /= acount
        amaxDepth /= acount
        aduration /= acount
            
        csv['header'].append('{}'.format(alg)) 
        csv['length'].append(alength) 
        csv['visited'].append(avisited) 
        csv['processed'].append(aprocessed) 
        csv['maxDepth'].append(amaxDepth) 
        csv['duration'].append(aduration) 
    
with open('summary.csv', 'w') as f:
    for header, line in csv.items():
        f.write(header + ',')
        f.write(','.join(map(str, line)) + '\n')
