class EditDistance():
    x = None
    y = None
    match = None
    mismatch = None
    matrix = []
    shift = None
    score = None

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self._calculate_matrix()
        self.score = self.matrix[-1][-1]
    
    def __str__(self):
        return self.score

    def _calculate_matrix(self):
        x = " " + self.x
        y = " " + self.y
        matrix = [ [0] + [self.shift * i for i in range(1, len(y))]]
        for i in range(1, len(x)):
            row = [self.shift * i]
            for j in range(1, len(y)):
                sij = self.match if x[i] == y[j] else self.mismatch
                row.append(min(
                    matrix[i-1][j-1] + sij,
                    matrix[i-1][j] + self.shift,
                    row[j-1] + self.shift
                ))
            matrix.append(row)
        self.matrix = matrix

class HammingDistance(EditDistance):
    match = 0
    mismatch = 1
    shift = float("inf")

    def __init__(self, x, y):
        if len(x) != len(y):
            raise ValueError("Undefined for sequences of unequal length")
        super().__init__(x, y)

class LevenshteinDistance(EditDistance):
    match = 0
    mismatch = 1
    shift = 1
