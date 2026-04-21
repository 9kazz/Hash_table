import matplotlib.pyplot as plt
from collections import Counter
import numpy as np

def build_histogram(filename, save_plot=True):
    
    cell_amount = 4000

    word_to_cell = {}
    
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split('\t')
            if len(parts) >= 2:
                word = parts[0]
                cell = int(parts[1])
                if word not in word_to_cell:
                    word_to_cell[word] = cell
    
    counter = Counter(word_to_cell.values())
    
    sorted_items = sorted(counter.items())
    cell_nums = [item[0] for item in sorted_items]
    counts = [item[1] for item in sorted_items]
    
    plt.figure(figsize=(12, 6))
    plt.bar(cell_nums, counts, color='steelblue', edgecolor='skyblue', alpha=0.7)
    plt.xlabel('Номер ячейки')
    plt.ylabel('Количество слов в ячейке')
    plt.title('Распределение слов в хэш-таблице\n')
    plt.text(0.5, 1.02, '(Crc32: 4000)', transform=plt.gca().transAxes, ha='center', fontsize=10, style='italic')
    plt.grid(True, alpha=0.3, axis='y')
    
    plt.text(0.02, 0.98, 
             f"Всего уникальных слов: {len(word_to_cell)}\n"
             f"Занято ячеек: {len(counter)}/{cell_amount} ({len(counter)/cell_amount*100:.1f}%)\n"
             f"Load Factor: {len(word_to_cell) / len(counter):.1f}\n"
             f"Макс. кол-во слов в ячейке: {max(counts)}\n"
             f"Дисперсия: {np.var(counts):.2f}\n"
             f"Корень дисперсии: {(np.var(counts))**0.5:.1f}",
             transform=plt.gca().transAxes,
             verticalalignment='top',
             bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    
    plt.tight_layout()
    if save_plot:
        plt.savefig('Files/Histogram.png', dpi=150)
    plt.show()

if __name__ == "__main__":
    build_histogram("Files/Statfile.csv")
