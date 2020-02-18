from ._alignment import Alignment


class SmithWaterman(Alignment):

    def _align(self):
        seq1, seq2 = " " + self.seq1, " " + self.seq2
        delta = self.delta
        matrix = [[0] * len(seq2)]

        for i in range(1, len(seq1)):
            row = [0]
            for j in range(1, len(seq2)):
                Sa = matrix[i-1][j-1] + self.subs_mat[seq1[i]][seq2[j]]
                Sb = matrix[i-1][j] - delta
                Sc = row[j-1] - delta
                Sij = max(Sa, Sb, Sc)
                if Sij < 0:
                    Sij = 0
                row.append(Sij)
            matrix.append(row)
        self.align_matrix = matrix
    
    def _trace_back(self):
        matrix = self.align_matrix
        seq1, seq2 = " " + self.seq1, " " + self.seq2
        i, j = self._get_best_score_position()

        alseq1 = list(seq1[i:])[::-1]
        alseq2 = list(seq2[j:])[::-1]

        ntail1, ntail2 = len(seq1[i:]), len(seq2[j:])
        if ntail1 > ntail2:
            alseq2 = [" "] * (ntail1 - ntail2) + alseq2
            almatches = [" "] * len(alseq1)
        else:
            alseq1 = [" "] * (ntail2 - ntail1) + alseq1
            almatches = [" "] * len(alseq2)
        
        stopIndex = (0,0)
        stopFound = False

        while i > 0 and j > 0 and not stopFound:
            diag = matrix[i-1][j-1] if i > 0 and j > 0 else -float("inf")
            up = matrix[i-1][j] if i > 0 else -float("inf")
            left = matrix[i][j-1] if j > 0 else -float("inf")
            best = max(diag, up, left)

            if not stopFound and best == 0:
                stopIndex = (i, j)
                stopFound = True
                continue
            
            if best == diag:
                alseq1.append(seq1[i])
                alseq2.append(seq2[j])
                almatches.append("|" if seq1[i] == seq2[j] else " ")
                i -= 1
                j -= 1
            elif best == up:
                alseq1.append(seq1[i])
                alseq2.append("-" if j > 0 else " ")
                almatches.append(" ")
                i -= 1
            else:
                alseq1.append("-" if i > 0 else " ")
                alseq2.append(seq2[j])
                almatches.append(" ")
                j -= 1
        
        alseq1 = alseq1 + list(seq1[:i+1])[::-1]
        alseq2 = alseq2 + list(seq2[:j+1])[::-1]

        if len(alseq1) > len(alseq2) :
            alseq2 = alseq2 + [" "] * (len(alseq1) - len(alseq2))
            almatches = almatches +  [" "] * (i + 1)
        else:
            alseq1 = alseq1 + [" "] * (len(alseq2) - len(alseq1))
            almatches = almatches + [" "] * (j + 1)
        
        self.alseq1 = "".join(alseq1[:-1][::-1])
        self.alseq2 = "".join(alseq2[:-1][::-1])
        self.almatches = "".join(almatches[:-1][::-1])
    
    def _get_best_score_position(self):
        matrix = self.align_matrix
        position = (0,0)
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                if matrix[i][j] > matrix[position[0]][position[1]]:
                    position = (i,j)
        return position