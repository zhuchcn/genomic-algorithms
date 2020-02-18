from .suffix_array import SuffixArray


class BurrowsWheeler():
    bwt = None
    dollar_row = None
    length = None
    cp_ival = None
    ssa_ival = None
    first_occur = {}
    checkpoints = {}

    def __init__(self, text, cp_ival=4, ssa_ival=4):
        text += "$"
        self.cp_ival = cp_ival
        self.ssa_ival = ssa_ival
        self.length = len(text)
        self.index(text)
        self.checkpoint()

    def transform(self, sa, text):
        '''
        This performs the Burrows-Wheeler transform of the text using suffix
        array.
        '''
        bwt = []
        for i in sa:
            if i == 0:
                self.dollar_row = len(bwt)
                bwt.append("$")
            else:
                bwt.append(text[i-1])
        self.bwt = "".join(bwt)
    
    def index(self, text):
        '''
        This calls the self.transform first, followed by creating the FM index
        per suffix array interval (ssa_ival).
        '''
        sa = SuffixArray(text).index
        self.transform(sa, text)

        # downsample the suffix array every ssa_ival
        ssa = {}
        for i in range(len(sa)):
            if i % self.ssa_ival == 0:
                ssa[i] = sa[i]
        self.ssa = ssa
                
        # get total occurrences of each nucleotide
        tots = {}
        for nt in self.bwt:
            tots[nt] = tots.get(nt, 0) + 1
        tot_nt = 0
        # this is the first occurrence of each nucleotide at first of each row
        for nt, count in sorted(tots.items()):
            self.first_occur[nt] = tot_nt
            tot_nt += count

    def checkpoint(self):
        '''
        This creates checkpoints for number of each nucleotides before and
        include the current one, for every ssa_ival.
        '''
        tally = {}

        # create a empty dict for all unique nucleotide
        for nt in self.bwt:
            if nt != "$" and nt not in tally:
                tally[nt] = 0
                self.checkpoints[nt] = []
            
        # add checkpoints
        for i in range(self.length):
            nt = self.bwt[i]
            if nt != "$":
                tally[nt] += 1
            if i % self.cp_ival == 0:
                for nt in tally.keys():
                    self.checkpoints[nt].append(tally[nt])
    
    def rank(self, nt, row):
        '''
        This returns the number of the same nucleotide before and include the
        current one, at a given row (position).
        This only walks up to the first checkpoint, rather than looking for the
        nearest checkpoint, which can be improved
        '''
        if row < 0 or nt not in self.checkpoints:
            return -1

        # TODO: find the nearest checkpoint rather than the first previous.
        i, j = row, 0

        while (i % self.cp_ival) != 0:
            if self.bwt[i] == nt:
                j += 1
            i -= 1
        return self.checkpoints[nt][i//self.cp_ival] + j

    def get_range(self, p):
        '''
        This returns the range of rows that match a pattern p. 
        '''
        left, right = 0, self.length - 1
        for i in range(len(p)-1, -1, -1):
            left = self.rank(p[i], left-1) + self.first_occur[p[i]]
            right = self.rank(p[i], right) + self.first_occur[p[i]] - 1
            if right < left:
                return None
        return left, right + 1

    def resolve(self, row):
        # walk up to the nearest ssa
        nsteps = 0
        while row not in self.ssa:
            nt = self.bwt[row]
            row = self.rank(nt, row-1) + self.first_occur[nt]
            nsteps += 1
        return self.ssa[row] + nsteps

    def query(self, p):
        _range = self.get_range(p)
        if not _range:
            return [-1]
        return [self.resolve(x) for x in range(_range[0], _range[1])]