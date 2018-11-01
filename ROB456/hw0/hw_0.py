import numpy as np
import matplotlib.pyplot as plt
np.random.seed(0)

##PART ONE####
def f_x(x_in):
    c = np.array([-0.1, 4.0, -0.1, 10.0], float)
    return np.polyval(c, x_in)
    
def plot_format(axh, x_limit = None, title = "", xlabel = "x", ylabel = "y"):
    if x_limit is not None:
        axh.set_xlim(x_limit)
    axh.set_title(title)
    axh.set_xlabel(xlabel)
    axh.set_ylabel(ylabel)
    
#Step 1 make a poly
xlim = [-10.0, 25.0]
x_min = xlim[0]
x_max = xlim[1]
x = np.linspace(x_min, x_max, num=351, dtype=float)
y = f_x(x)

#Step 2 plot the poly
fhl, axhl = plt.subplots()
axhl.plot(x, y, 'b-')
plot_format(axhl, xlim, 'Origional poly')
fhl.savefig('hw0_origional_polynomial.pdf', bbox_inches = 'tight')


#Step 3: Plot discretized bins
b_width = (x_max - x_min)/14.0
x = x_bin = np.arange(x_min, x_max, step=b_width, dtype=float)
y = y_bin = f_x(x_bin)
fh2, axh2 = plt.subplots()
axh2.bar(x + b_width / 2, y, width=b_width, edgecolor='k')
plot_format(axh2, x_limit=xlim, title="Discretized Bins" )
fh2.savefig('hw0_discretized_bins.pdf', bbox_inches = 'tight')

###Step 4 turn into pdf
y_bin_norm = y / y.sum()
fh3, axh3 = plt.subplots()
axh3.bar(x + b_width / 2.0, y_bin_norm, width=b_width, edgecolor='k')
plot_format(axh3, xlim, "Discrete bins (normalized), sum = %s" %(y_bin_norm.sum()), ylabel = 'p(x)')
fh3.savefig('hw0_discretized_bins_normalized.pdf', bbox_inches = 'tight')

n_samples = 500
x = x_rand = np.arange(1, n_samples + 1, step=1, dtype=int)
y = y_rand = np.random.random(n_samples)
fh4, axh4, = plt.subplots()
axh4.plot(x, y, "k+")
plot_format(axh4, [1, n_samples], " %s samples, uniformly distributed" % n_samples)
fh4.savefig('hw0_discretized_bins_normalized.pdf', bbox_inches = 'tight')

###5.2 (incorrect) plot bin ranges
y_scaled = y * (x_max - x_min) + x_min
fh5, axh5 = plt.subplots()
axh5.plot(x, y_scaled, "k+")
for i in range(0, len(x_bin)):
    axh5.plot([1, n_samples], [x_bin[i], x_bin[i]])
plot_format(axh5, [1, n_samples], 'Random samples mapped to x ranges of bins')
fh5.savefig('hw0_random_to_bin_ranges.pdf', bbox_inches = 'tight')

##
#5.3 shift points (incorrect)
y_count_incorrect = np.zeros(x_bin.shape)
for i in range(0, len(y_scaled)):
    for j in range(len(x_bin), 0, -1):
        if y_scaled[i] > x_bin[j-1]:
            y_count_incorrect[j-1] += 1
            break
fh6, axh6 = plt.subplots()
axh6.bar(x_bin + b_width/2.0, y_count_incorrect, width = b_width, edgecolor = 'k')
plot_format(axh6, xlim, 'Samples per bin (incorrect)', ylabel = 'samples')
fh6.savefig('hw0_samples_incorrect.pdf', bbox_inches = 'tight')

##
#5.3 shift points correct
y_bin_cdf = y_bin_norm.copy()
i = 0
while i < len(y_bin_cdf) - 1:
    i += 1
    y_bin_cdf[i] += y_bin_cdf[i-1]
    
fh7, axh7 = plt.subplots()
axh7.plot(x_rand, y_rand, 'k+')
for i in range(0, len(y_bin_cdf)):
    axh7.plot([1, n_samples], [y_bin_cdf[i], y_bin_cdf[i]])
plot_format(axh7, [1, n_samples], 'Samples points per bin (correct)', ylabel='samples')
fh7.savefig('hw0_samplepoints_correct.pdf', bbox_inches = 'tight')

#Plot samples per bin correct
y_count_correct = np.zeros(x_bin.shape)
for i in range(0, len(y_rand)):
    for j in range(0, len(y_bin_cdf)):
        if y_rand[i] < y_bin_cdf[j]:
            y_count_correct[j] += 1
            break
fh8, axh8 = plt.subplots()
axh8.bar(x_bin + b_width/2.0, y_count_correct, width = b_width, edgecolor = 'k')
plot_format(axh8, xlim, 'Samples per bin (correct)', ylabel = 'samples')
fh8.savefig('hw0_samples_correct.pdf', bbox_inches = 'tight')


### Part II: Representing a pdf as a distribution of particles
xlim = [-10.0, 25.0]
x = np.linspace(xlim[0], xlim[1], 351, float)
y = f_x(x)

# Normalize original polynomial plot
p_area = y.sum() * (x[1]-x[0])
y_norm = y/p_area

# Create a figure handle to contain subplots
fh10 = plt.figure(figsize=(12, 4))

# Step 1: Generate 500 uniformly distributed samples in the range 0 to 1 as you did in Step 5.1 above.
# This time, for each sample, store two numbers - an x value (found by shifting the sample to lie in [-10,25], as in 5.2 above) and a y value
# (found by evaluating the polynomial at x). Normalize the polynomial (and the samples) as in Step 6 above.
n_samples = 500
s_rand = np.zeros([n_samples, 2])
s_rand[:, 0] = np.random.random(n_samples)
s_rand[:, 0] = s_rand[:, 0] * (xlim[1] - xlim[0]) + xlim[0]
s_rand[:, 1] = f_x(s_rand[:, 0]) / p_area

axh10a = fh10.add_subplot(131)
axh10a.plot(x, y_norm, 'b-', label='Normalized polynomial')
axh10a.plot(s_rand[:, 0], s_rand[:, 1], 'k+', label='Samples')
plot_format(axh10a, title='Normalized polynomial with samples', ylabel='p(x)')
axh10a.legend()
fh10.savefig('hw0_norm_samples.pdf', bbox_inches = 'tight')

y_bin_cdf = y_bin_norm.copy()
i = 0
while i < len(y_bin_cdf) - 1:
    i += 1
    y_bin_cdf[i] += y_bin_cdf[i-1]
fh11, axh11 = plt.subplots()
axh11.plot(s_rand[:, 0], s_rand[:, 1], 'k+')
for i in range(0, len(y_bin_cdf)):
    axh11.plot([1, n_samples], [y_bin_cdf[i], y_bin_cdf[i]])
plot_format(axh11, [1, n_samples], 'Samples Dist.', ylabel = 'samples')
fh11.savefig('hw0_disctre_norm_samples.pdf', bbox_inches = 'tight')

y_count_correct = np.zeros(x_bin.shape)
for i in range(0, len(y_rand)):
    for j in range(0, len(y_bin_cdf)):
        if y_rand[i] < y_bin_cdf[j]:
            y_count_correct[j] += 1
            break
fh12, axh12 = plt.subplots()
axh12.bar(x_bin + b_width/2.0, y_count_correct, width = b_width, edgecolor = 'k')
plot_format(axh12, xlim, 'Samples Shown', ylabel = 'samples')
fh10.savefig('hw0_samples_shown.pdf', bbox_inches = 'tight')

n_samples = 5000
s_rand = np.zeros([n_samples, 3])
s_rand[:, 0] = np.random.random(n_samples)
s_rand[:, 0] = s_rand[:, 0] * (xlim[1] - xlim[0]) + xlim[0]
s_rand[:, 1] = f_x(s_rand[:, 0]) / p_area

fh13 = plt.figure(figsize=(12, 4))
axh13a = fh13.add_subplot(131)
axh13a.plot(x, y_norm, 'b-', label='Normalized polynomial')
axh13a.plot(s_rand[:, 0], s_rand[:, 1], 'k+', label='Samples')
plot_format(axh13a, title='Normalized polynomial with samples', ylabel='p(x)')
axh13a.legend()
fh13.savefig('hw0_norm_samples.pdf', bbox_inches = 'tight')

y_bin_cdf = y_bin_norm.copy()
i = 0
while i < len(y_bin_cdf) - 1:
    i += 1
    y_bin_cdf[i] += y_bin_cdf[i-1]
fh14, axh14 = plt.subplots()
axh14.plot(s_rand[:, 0], s_rand[:, 1], 'k+')
for i in range(0, len(y_bin_cdf)):
    axh14.plot([1, n_samples], [y_bin_cdf[i], y_bin_cdf[i]])
plot_format(axh14, [1, n_samples], 'Samples Dist.', ylabel = 'samples')
fh14.savefig('hw0_norm_samples_dis.pdf', bbox_inches = 'tight')

y_count_correct = np.zeros(x_bin.shape)
for i in range(0, len(y_rand)):
    for j in range(0, len(y_bin_cdf)):
        if y_rand[i] < y_bin_cdf[j]:
            y_count_correct[j] += 1
            break
fh15, axh15 = plt.subplots()
axh15.bar(x_bin + b_width/2.0, y_count_correct, width = b_width, edgecolor = 'k')
plot_format(axh15, xlim, 'Samples Shown', ylabel = 'samples')
fh15.savefig('hw0_norm_samples_shown.pdf', bbox_inches = 'tight')

plt.show()
