from module.pysparse import *

data = [
    (0, [(0, 1), (1, 2)]),
    (1, [(0, 3), (1, 4)])
]

a = Int64SparseMatrix(data)
b = Int64SparseMatrix(data)
r = a @ b

print(r.to_dict())
