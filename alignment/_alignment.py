class Alignment():
    seq1 = None
    seq2 = None
    delta = 1
    align_matrix = None
    alseq1 = None
    alseq2 = None
    almatch = None
    subs_mat = {
        "A": {"A": 1,    "C": -1,   "G": -1, "T": -1  },
        "C": {"A": -1,   "C": 1,    "G": -1,   "T": -1},
        "G": {"A": -1, "C": -1,   "G": 1,    "T": -1  },
        "T": {"A": -1,   "C": -1, "G": -1,   "T": 1   }
    }
    range = None

    def __init__(self, seq1, seq2):
        self.seq1, self.seq2 = seq1, seq2
        self._align()
        self._trace_back()
    
    def __str__(self):
        return "\n" +\
            "seq1:   " + self.alseq1 + "\n" + \
            "        " + self.almatches + "\n" +\
            "seq2:   " + self.alseq2
    
    def _align(self):
        pass

    def _trace_back(self):
        pass
