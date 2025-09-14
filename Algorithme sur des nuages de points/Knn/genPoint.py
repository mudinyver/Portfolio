import random
def gen(NB_POINTS=22,MAX=1057,nbDim=2):
    random_nb=[]
    for n in range (NB_POINTS):
        random_nb.append(random.sample(range(-MAX-1,MAX+ 1), nbDim))
    return random_nb