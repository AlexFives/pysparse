from typing import List, Tuple, Dict


class ViewCaseError(Exception):
    ...


class ShapeIterator:
    def __next__(self) -> int:
        ...


class Shape:
    def __eq__(self, other: 'Shape') -> bool:
        ...

    def __ne__(self, other: 'Shape') -> bool:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> int:
        ...

    def __iter__(self) -> ShapeIterator:
        ...


class Int32SparseMatrixView:
    def is_value(self) -> bool:
        ...

    def value(self) -> int:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> int:
        ...


class Int64SparseMatrixView:
    def is_value(self) -> bool:
        ...

    def value(self) -> int:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> int:
        ...


class FloatSparseMatrixView:
    def is_value(self) -> bool:
        ...

    def value(self) -> int:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> float:
        ...


class DoubleSparseMatrixView:
    def is_value(self) -> bool:
        ...

    def value(self) -> int:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> float:
        ...


class LongDoubleSparseMatrixView:
    def is_value(self) -> bool:
        ...

    def value(self) -> int:
        ...

    def __len__(self) -> int:
        ...

    def __getitem__(self, index: int) -> float:
        ...


class Int32SparseMatrixIterator:
    def __next__(self) -> Int32SparseMatrixView:
        ...


class Int64SparseMatrixIterator:
    def __next__(self) -> Int64SparseMatrixView:
        ...


class FloatSparseMatrixIterator:
    def __next__(self) -> FloatSparseMatrixView:
        ...


class DoubleSparseMatrixIterator:
    def __next__(self) -> DoubleSparseMatrixView:
        ...


class LongDoubleSparseMatrixIterator:
    def __next__(self) -> LongDoubleSparseMatrixIterator:
        ...


class Int32SparseMatrix:
    def __init__(self, data: List[Tuple[int, List[Tuple[int, int]]]]):
        ...

    def __init__(self, data: Dict[int, Dict[int, int]]):
        ...

    def to_list(self) -> List[Tuple[int, List[Tuple[int, int]]]]:
        ...

    def to_dict(self) -> Dict[int, Dict[int, int]]:
        ...

    def __add__(self, other: 'Int32SparseMatrix') -> 'Int32SparseMatrix':
        ...

    def __sub__(self, other: 'Int32SparseMatrix') -> 'Int32SparseMatrix':
        ...

    def __mul__(self, other: 'Int32SparseMatrix') -> 'Int32SparseMatrix':
        ...

    def __mul__(self, other: int) -> 'Int32SparseMatrix':
        ...

    def __truediv__(self, other: 'Int32SparseMatrix') -> 'Int32SparseMatrix':
        ...

    def __truediv__(self, other: int) -> 'Int32SparseMatrix':
        ...

    def __matmul__(self, other: 'Int32SparseMatrix') -> 'Int32SparseMatrix':
        ...

    def transpose(self) -> 'Int32SparseMatrix':
        ...

    def shape(self) -> Shape:
        ...

    def __iter__(self) -> Int32SparseMatrixIterator:
        ...


class Int64SparseMatrix:
    def __init__(self, data: List[Tuple[int, List[Tuple[int, int]]]]):
        ...

    def __init__(self, data: Dict[int, Dict[int, int]]):
        ...

    def to_list(self) -> List[Tuple[int, List[Tuple[int, int]]]]:
        ...

    def to_dict(self) -> Dict[int, Dict[int, int]]:
        ...

    def __add__(self, other: 'Int64SparseMatrix') -> 'Int64SparseMatrix':
        ...

    def __sub__(self, other: 'Int64SparseMatrix') -> 'Int64SparseMatrix':
        ...

    def __mul__(self, other: 'Int64SparseMatrix') -> 'Int64SparseMatrix':
        ...

    def __mul__(self, other: int) -> 'Int64SparseMatrix':
        ...

    def __truediv__(self, other: 'Int64SparseMatrix') -> 'Int64SparseMatrix':
        ...

    def __truediv__(self, other: int) -> 'Int64SparseMatrix':
        ...

    def __matmul__(self, other: 'Int64SparseMatrix') -> 'Int64SparseMatrix':
        ...

    def transpose(self) -> 'Int64SparseMatrix':
        ...

    def shape(self) -> Shape:
        ...

    def __iter__(self) -> Int64SparseMatrixIterator:
        ...


class FloatSparseMatrix:
    def __init__(self, data: List[Tuple[int, List[Tuple[int, float]]]]):
        ...

    def __init__(self, data: Dict[int, Dict[int, float]]):
        ...

    def to_list(self) -> List[Tuple[int, List[Tuple[int, float]]]]:
        ...

    def to_dict(self) -> Dict[int, Dict[int, float]]:
        ...

    def __add__(self, other: 'FloatSparseMatrix') -> 'FloatSparseMatrix':
        ...

    def __sub__(self, other: 'FloatSparseMatrix') -> 'FloatSparseMatrix':
        ...

    def __mul__(self, other: 'FloatSparseMatrix') -> 'FloatSparseMatrix':
        ...

    def __mul__(self, other: int) -> 'FloatSparseMatrix':
        ...

    def __truediv__(self, other: 'FloatSparseMatrix') -> 'FloatSparseMatrix':
        ...

    def __truediv__(self, other: int) -> 'FloatSparseMatrix':
        ...

    def __matmul__(self, other: 'FloatSparseMatrix') -> 'FloatSparseMatrix':
        ...

    def transpose(self) -> 'FloatSparseMatrix':
        ...

    def shape(self) -> Shape:
        ...

    def __iter__(self) -> FloatSparseMatrixIterator:
        ...


class DoubleSparseMatrix:
    def __init__(self, data: List[Tuple[int, List[Tuple[int, float]]]]):
        ...

    def __init__(self, data: Dict[int, Dict[int, float]]):
        ...

    def to_list(self) -> List[Tuple[int, List[Tuple[int, float]]]]:
        ...

    def to_dict(self) -> Dict[int, Dict[int, float]]:
        ...

    def __add__(self, other: 'DoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __sub__(self, other: 'DoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __mul__(self, other: 'DoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __mul__(self, other: int) -> 'DoubleSparseMatrix':
        ...

    def __truediv__(self, other: 'DoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __truediv__(self, other: int) -> 'DoubleSparseMatrix':
        ...

    def __matmul__(self, other: 'DoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def transpose(self) -> 'DoubleSparseMatrix':
        ...

    def shape(self) -> Shape:
        ...

    def __iter__(self) -> DoubleSparseMatrixIterator:
        ...


class LongDoubleSparseMatrix:
    def __init__(self, data: List[Tuple[int, List[Tuple[int, float]]]]):
        ...

    def __init__(self, data: Dict[int, Dict[int, float]]):
        ...

    def to_list(self) -> List[Tuple[int, List[Tuple[int, float]]]]:
        ...

    def to_dict(self) -> Dict[int, Dict[int, float]]:
        ...

    def __add__(self, other: 'LongDoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __sub__(self, other: 'LongDoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __mul__(self, other: 'LongDoubleSparseMatrix') -> 'DoubleSparseMatrix':
        ...

    def __mul__(self, other: int) -> 'LongDoubleSparseMatrix':
        ...

    def __truediv__(self, other: 'LongDoubleSparseMatrix') -> 'LongDoubleSparseMatrix':
        ...

    def __truediv__(self, other: int) -> 'LongDoubleSparseMatrix':
        ...

    def __matmul__(self, other: 'LongDoubleSparseMatrix') -> 'LongDoubleSparseMatrix':
        ...

    def transpose(self) -> 'LongDoubleSparseMatrix':
        ...

    def shape(self) -> Shape:
        ...

    def __iter__(self) -> LongDoubleSparseMatrixIterator:
        ...
