from pysparse import *

data = [
    (0, [(0, 1), (1, 2)]),
    (1, [(0, 3), (1, 4)])
]

a = DoubleSparseMatrix(data)
b = DoubleSparseMatrix(data)
r = a + b
rt = r.transpose()

print(r.to_dict())
print(rt.to_dict())
