import matplotlib.pyplot as plt


f = figure(1)

for j in 1:4
  subplot(2,2,j)
  plot(rand(10), rand(10))
end

# these lines do nothing for me, and I cannot understand why.
subplots_adjust(hspace = 0.01)
subplots_adjust(wspace = 0.01)