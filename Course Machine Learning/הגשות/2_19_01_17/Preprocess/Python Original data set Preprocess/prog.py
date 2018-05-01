from random import shuffle

with open("kdd_for_HW_original.csv") as f:
    lines = f.readlines()

shuffle(lines)

"""
k = 0;
for row in lines[:]:
    samples = row.split(",")
    if str(samples[len(samples) - 1]).startswith('normal.'):
        samples[len(samples) - 1] = "0\n"
    else:
        samples[len(samples) - 1] = "1\n"
    lines[k] = ",".join(samples)
    k = k + 1
"""

with open("kdd_for_HW_original_shuffled.csv", 'w') as f:
    f.writelines(lines)
