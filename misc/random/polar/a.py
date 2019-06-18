import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

"""
r = np.arange(0, 2, 0.01)
theta = 2 * np.pi * r
"""

def fun(theta):
    return np.sin(4*theta)

MAX_TH = 2*np.pi #max value of theta
MAX_R = 5
STEP = 0.001

graph = plt.subplot(111, projection='polar')
graph.set_rticks(np.arange(0,MAX_R,MAX_R/5))  # Less radial ticks
graph.set_rlabel_position(-22.5)  # Move radial labels away from plotted line
graph.grid(True)

def update(val):
    #print("OK")
    tt = samp.val;
    theta = np.arange(0,tt,STEP)
    r = fun(theta)
    for i in range(len(theta)):
        if (r[i] < 0) :
            theta[i] = (theta[i] + np.pi) % (2*np.pi)
            r[i] = -r[i]

    graph.clear()
    graph.plot(theta,r)
    #graph.set_rmax(sliderR.val)

#set theta slider
axcolor = 'lightgoldenrodyellow'
axamp = plt.axes([0.2, 0.05, 0.65, 0.03], facecolor=axcolor)
#maxR = plt.axes([0,2, 0.1, 0.65, 0.03], facecolor = axcolor)
samp = Slider(axamp, 'Theta', 0.01, MAX_TH, valinit=MAX_TH)
samp.on_changed(update)

#sliderR = Slider(maxR, 'Max Radius', 0.01, MAX_R, valinit = 2)
#sliderR.on_changed(update)


graph.set_title("Test", va='bottom')
update(MAX_TH)
plt.show()
