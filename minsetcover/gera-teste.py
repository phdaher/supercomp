import random


def random_subset(s, D_size):
    D = set(random.sample(s, k=D_size))
    return D


def gera_input(U_size, F_size, D_size, Output):
    """
      U_size = número de elementos em U
      F_size = número de elementos em F
      D_size = número máximo de elementos em cada subconjunto de F
      Output = nome do arquivo de output
    """
    output = f'{U_size} {F_size}\n'

    subsets = []
    universe = set(range(U_size))

    for i in range(F_size):
        d = random.randint(1, D_size)
        subset = random_subset(universe, d)
        if len(subset) != 0:
            subsets.append(subset)
            output += str(subset)[1:-1].replace(',', "") + "\n"
    with open(Output, "w") as text_file:
        text_file.write(output)


gera_input(200, 120, 60, "teste.txt")
