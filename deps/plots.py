import matplotlib.pyplot as plt
import json

parameters = {'bfs': ['rdul', 'rdlu', 'ludr', 'lurd'], 'dfs': ['rdul', 'rdlu', 'ludr', 'lurd'], 'astr': ['manh', 'hamm', 'mdlc']}

labels = {'rdul': 'rdul/drlu', 'rdlu': 'rdlu/drul', 'ludr': 'ludr/ulrd', 'lurd': 'lurd/uldr', 'manh': 'manh', 'hamm': 'hamm', 'mdlc': 'mdlc'}

colors = ['#557f2d', '#2d7f5e', '#69e007', '#7f6d5f', '#8cce4a', '#d9d047', '#043d20', '#7a7538']

colors4 = ['#e66101', '#fdb863', '#b2abd2', '#5e3c99']
colors3 = ['#f1a340','#bfbac0','#897eb3']

data = {}
with open('summary.json', 'r') as f:
    data = json.loads(f.read())

for statistic, ylabel in [['duration', 'czas przetwarzania [ms]'], ['visited', 'ilość odwiedzonych wierzchołków'], ['processed', 'ilość przetworzonych wierzchołków'], ['maxDepth', 'maksymalna głębokość'], ['length', 'długość rozwiązania']]:
    inter_stat = {}
    for alg in ['dfs', 'bfs', 'astr']: 
        inter_stat[alg] = [0 for _ in range(7)]
    
    for alg in ['dfs', 'bfs', 'astr']:  
        stat_values = {}
        for par in parameters[alg]:
            stat_values[par] = []
        for lvl in range(1, 8):
            for par in parameters[alg]:
                stat_values[par].append(data[str(lvl)][alg][par][statistic])
           
        for values in stat_values.values():
            for i, v in enumerate(values):
                inter_stat[alg][i] += v
        
        for i in range(len(inter_stat[alg])):
            inter_stat[alg][i] /= len(parameters[alg])
                
        bars = []
        ranges = []
        barWidth = 0.
        wadd = 0.25 if len(stat_values) == 3 else 0.2
        for key, value in stat_values.items():
            bars.append([value, labels[key]])
            ranges.append([x + barWidth for x in range(len(value))])
            barWidth += wadd
            
        # Make the plot
        plt.figure()
        for r, bl, c in zip(ranges, bars, colors3 if len(ranges)==3 else colors4):
            plt.bar(r, bl[0], color=c, width=wadd, edgecolor='white', label=bl[1])
     
        plt.title(alg, fontweight='bold')
        plt.ylabel(ylabel, fontweight='bold')
        # Add xticks on the middle of the group bars
        plt.xlabel('poziom', fontweight='bold')
        offset = 0.25 if len(bars) == 3 else 0.3
        plt.xticks([r + offset for r in range(len(bars[0][0]))], range(1, len(bars[0][0])+1))
     
        # Create legend & Show graphic
        plt.legend()
        plt.savefig('{}_{}.pdf'.format(alg, statistic))
        
    bars = []
    ranges = []
    barWidth = 0.
    wadd = 0.33 if statistic in ['duration', 'processed', 'visited'] else 0.25
    for key, value in inter_stat.items():
        if statistic in ['duration', 'processed', 'visited'] and key == 'dfs':
            continue
        bars.append([value, key])
        ranges.append([x + barWidth for x in range(len(value))])
        barWidth += wadd
        
    # Make the plot
    plt.figure()
    for r, bl, c in zip(ranges, bars, colors3 if len(ranges)==3 else [colors4[0], colors4[3]]):
        plt.bar(r, bl[0], color=c, width=wadd, edgecolor='white', label=bl[1])
 
    plt.title(statistic, fontweight='bold')
    plt.ylabel(ylabel, fontweight='bold')
    # Add xticks on the middle of the group bars
    plt.xlabel('poziom', fontweight='bold')
    offset = 0.25
    plt.xticks([r + offset for r in range(len(bars[0][0]))], range(1, len(bars[0][0])+1))
 
    # Create legend & Show graphic
    plt.legend()
    plt.savefig('all_{}.pdf'.format(statistic))
