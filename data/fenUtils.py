# utils for other scripts, most notably bitify and fenify positions

# top left = 0, bottom right = 63
def getBBSquare(square):
    res = [0] * 64
    res[square] = 1
    return res

def bitifyFEN(fen):
    splitFen = fen.split()
    pieces = [[0 for sq in range(64)] for p in range(12)] # P p N n B b R r Q q K k
    res = []
    square = 0

    for c in splitFen[0]:
        if (c.isdigit()):
            square += int(c)
        elif(c == "P"):
            pieces[0][square] = 1
            square += 1
        elif(c == "p"):
            pieces[1][square] = 1
            square += 1
        elif(c == "N"):
            pieces[2][square] = 1
            square += 1
        elif(c == "n"):
            pieces[3][square] = 1
            square += 1
        elif(c == "B"):
            pieces[4][square] = 1
            square += 1
        elif(c == "b"):
            pieces[5][square] = 1
            square += 1
        elif(c == "R"):
            pieces[6][square] = 1
            square += 1
        elif(c == "r"):
            pieces[7][square] = 1
            square += 1
        elif(c == "Q"):
            pieces[8][square] = 1
            square += 1
        elif(c == "q"):
            pieces[9][square] = 1
            square += 1
        elif(c == "K"):
            pieces[10][square] = 1
            square += 1
        elif(c == "k"):
            pieces[11][square] = 1
            square += 1

    for p in pieces:
        res.extend(p)

    if(splitFen[1] == "W"):
        res.append(0)
    else:
        res.append(1)

    if(splitFen[2].find("Q") != -1):
        res.append(1)
    else:
        res.append(0)

    if(splitFen[2].find("K") != -1):
        res.append(1)
    else:
        res.append(0)
    
    if(splitFen[2].find("q") != -1):
        res.append(1)
    else:
        res.append(0)

    if(splitFen[2].find("k") != -1):
        res.append(1)
    else:
        res.append(0)

    return res