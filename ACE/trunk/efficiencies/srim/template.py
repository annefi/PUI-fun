def TemplateReplace(templ, fout, repl):
    """
    Replace certain strings in the templ file with
    the replacements in the repl array and write the result into fout.
    This function does not open or close file.
    
    templ: Open template file
    fout: Open output file

    repl: Array of replacement pairs, with the first of each pair
    being the string to the search for and the second one the string.

    This function uses a simple but very inefficient O(n^2)
    algorithm. Do not use TOO MANY variables in your template.
    """

    for l in templ:
        n=l
        for (s,r) in repl:
            # s: search string
            # r: replacement
#           print "Replacing %s with %s" % (s,r)
            n=n.replace(s, str(r))
        fout.write(n)

