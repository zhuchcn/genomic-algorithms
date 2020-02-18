from ._alignment import Alignment


class SemiGlobal(Alignment):
    def __init__(self, seq1, seq2):
        if len(seq1) > len(seq2):
            raise ValueError("seq1 must not be longer than seq2")
        super().__init__(seq1, seq2)
    
    def _align(self):
        seq1, seq2 = " " + self.seq1, " " + self.seq2
        delta = self.delta
        matrix = [[0] * len(seq2)]

        for i in range(1, len(seq1)):
            row = [-delta * i]
            for j in range(1, len(seq2)):
                Sa = matrix[i-1][j-1] + self.subs_mat[seq1[i]][seq2[j]]
                Sb = matrix[i-1][j] - delta
                Sc = row[j-1] - delta
                Sij = max(Sa, Sb, Sc)
                row.append(Sij)
            matrix.append(row)
        self.align_matrix = matrix
    
    def _trace_back(self):
        matrix = self.align_matrix
        seq1, seq2 = " " + self.seq1, " " + self.seq2
        i = len(matrix) - 1
        j = matrix[-1].index(max(matrix[-1]))
        
        alseq1 = list(" " * (len(seq2) - j - 1) + seq1[i])
        alseq2 = list(seq2[j:])[::-1]
        almatches = [" "] * (len(seq2) - j)

        while i > 0 or j > 0:
            diag = matrix[i-1][j-1] if i > 0 and j > 0 else -float("inf")
            up = matrix[i-1][j] if i > 0 else -float("inf")
            left = matrix[i][j-1] if j > 0 else -float("inf")
            best = max(diag, up, left)

            if best == diag:
                alseq1.append(seq1[i])
                alseq2.append(seq2[j])
                almatches.append("|" if seq1[i] == seq2[j] else " ")
                i -= 1
                j -= 1
            elif best == up:
                alseq1.append(seq1[i])
                alseq2.append("-")
                almatches.append(" ")
                i -= 1
            else:
                alseq1.append("-" if i > 0 else " ")
                alseq2.append(seq2[j])
                almatches.append(" ")
                j -= 1
        
        self.alseq1 = "".join(alseq1[::-1])
        self.alseq2 = "".join(alseq2[::-1])
        self.almatches = "".join(almatches[::-1])