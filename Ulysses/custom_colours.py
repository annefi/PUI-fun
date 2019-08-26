from colorsys import rgb_to_hls, hls_to_rgb
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from numpy import array, zeros

def adjust_color_lightness(r, g, b, factor):
    h, l, s = rgb_to_hls(r / 255.0, g / 255.0, b / 255.0)
    l = max(min(l * factor, 1.0), 0.0)
    r, g, b = hls_to_rgb(h, l, s)
    return array([int(r * 255), int(g * 255), int(b * 255)])


def lighten_color(rgb, factor=0.1):
    r = rgb[0]
    g = rgb[1]
    b = rgb[2]
    return adjust_color_lightness(r, g, b, 1 + factor)


def darken_color(rgb, factor=0.1):
    r = rgb[0]
    g = rgb[1]
    b = rgb[2]
    return adjust_color_lightness(r, g, b, 1 - factor)

