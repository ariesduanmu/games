# -*- coding: utf-8 -*-
import argparse
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from scipy.spatial.distance import squareform, pdist, cdist
from numpy.linalg import norm

class Birds():
    def __init__(self, n, width=640, height=480):
        self.pos = [width/2, height/2] + 10 * np.random.rand(2*n).reshape(n, 2)
        angles = 2*math.pi*np.random.rand(n)
        self.vel = np.array(list(zip(np.sin(angles), np.cos(angles))))
        self.n = n
        self.minDist = 25.0
        self.maxRuleVel = 0.03
        self.maxVel = 2.0

    def tick(self, frameNum, pts, beak):
        self.distMatrix = squareform(pdist())

def parse_arguments():
    parser = argparse.ArgumentParser(description="Implementing Craig Reynold's Boids...")
    parser.add_argument('-n','--num_boids', default=100, required=False)
    args = parser.parse_args()
    return args

def main():
    args = parse_arguments():


if __name__ == "__main__":
    main()