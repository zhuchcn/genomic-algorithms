from ._alignment import Alignment


class NeedlemanWunsch(Alignment):
    def _align(self):
        seq1 = " " + self.seq1
        seq2 = " " + self.seq2
        delta = self.delta
        matrix = [[- delta * i for i in range(len(seq2))]]
        
        for i in range(1, len(seq1)):
            row = [- delta * i]
            
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
        j = len(matrix[0]) - 1

        alseq1 = []
        alseq2 = []
        matches = []

        while i > 0 and j > 0:
            diag = matrix[i-1][j-1]
            up = matrix[i-1][j-1]
            left = matrix[i][j-1]
            best = max(diag, up, left)

            if best == diag:
                alseq1.append(seq1[i])
                alseq2.append(seq2[j])
                matches.append("|" if seq1[i] == seq2[j] else " ")
                i -= 1
                j -= 1
            elif best == up:
                alseq1.append(seq1[i])
                alseq2.append("-")
                matches.append(" ")
                i -= 1
            else:
                alseq1.append("-")
                alseq2.append(seq2[j])
                matches.append(" ")
                j -= 1
        self.alseq1 = "".join(alseq1[::-1])
        self.alseq2 = "".join(alseq2[::-1])
        self.almatches = "".join(matches[::-1])