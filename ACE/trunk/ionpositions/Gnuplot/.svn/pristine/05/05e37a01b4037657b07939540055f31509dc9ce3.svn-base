# small helper functions
        
def MakeSureDirExists(dir):
    from os import mkdir
    try:
        mkdir(dir)
    except OSError, e:
        from errno import EEXIST
        if e.errno!=EEXIST:
            raise

def extractPlots(fn):
    """ Extract list of plot items from a saved GNUPlot state file (and only such a file!)
    Returns a list of pair, each pair corresponds to one plot. The first entry of the pair
    determines the kind of the file to plot, the second corresponds to the plot string.
    first pair:
    0 : the plot items is a GNUplot function
    1 : the plot item is a simple file
    2 : the plot item is a piped item (the string will be the pipe command, without "< ")
    """
    # FIXME
    pass

