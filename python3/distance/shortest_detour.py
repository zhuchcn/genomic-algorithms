import math


class ShortestDetour():
    x = None
    y = None
    t = None
    delta = 1
    shift = 1
    match = 0
    mismatch = 1
    matrix = []
    score = None

    def __init__(self, x, y, t):
        if len(x) > len(y):
            raise ValueError("x must not be longer than y")
        if len(y) - len(x) > t:
            raise ValueError(f"the distance is at least {t}")
        self.x, self.y, self.t = x, y, t
        self._init_matrix()
        self._fill_matrix()
        self.score = self.matrix[-1][-1]
    
    def __str__(self):
        return f'Score: {self.score}'
    
    def _init_matrix(self):
        self.matrix = [
            [None for j in range(len(self.y) + 1)] \
                for i in range(len(self.x) + 1)
        ]
    
    def _fill_matrix(self):
        matrix, shift, delta = self.matrix, self.shift, self.delta
        x = " " + self.x
        y = " " + self.y

        x_depth = math.ceil(self.t/(2 * self.delta) - (len(y) - len(x))/2)
        y_depth = len(y) - len(x) + x_depth

        for i in range(len(x)):
            left = i - x_depth
            right = left + x_depth + y_depth + 1

            if left < 0:
                left = 0
            if right > len(y):
                right = len(y)
            
            for j in range(left, right):
                if i == 0:
                    matrix[i][j] = shift * j
                    continue
                if j == left:
                    if i <= x_depth:
                        matrix[i][j] = shift * i
                        continue
                    Dij1 = float("inf")
                else:
                    Dij1 = matrix[i][j-1]
                
                if j == right - 1 and i <= len(x) - x_depth:
                    Di1j = float("inf")
                else:
                    Di1j = matrix[i-1][j]
                
                Di1j1 = matrix[i-1][j-1]

                Sij = self.match if x[i] == y[j] else self.mismatch
                matrix[i][j] = min(Di1j1 + Sij, Dij1 + shift, Di1j + shift)
        