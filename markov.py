#!/usr/bin/env python3

# replaced counter with list, because I end up unfolding it anyway
# from collections import Counter
import random
import itertools
import re

class Markov_gen():

    def __init__(self, n):
        # holds ngram as key with following word as val
        self.structure = {}
        # ngrams from the start of each text
        self.begins = []
        # n is ngrams size
        self.n = n

    # internal function to build the data structure
    def _ngrams(self, s):
        structure = self.structure
        n = self.n
        s = s.split(' ')
        lead_in = s[:n]
        self.begins.append(lead_in)
        for pos in range(len(s) - n):
            next = s[n+pos]
            lead_tuple = tuple(lead_in)
            if lead_tuple not in structure:
                structure[lead_tuple] = [next]
            else:
                structure[lead_tuple].append(next)
            lead_in.pop(0)
            lead_in.append(next)

    # add a text for reference
    def add_text(self, s):
        if len(s) < self.n:
            raise Exception
        self._ngrams(s)

    # generate a list from the texts
    def generate(self, n):
        s = []
        # choose a beginning 
        s += random.choice(self.begins)
        while len(s) < n:
            lead_in = tuple(s[-self.n:])
            try:
                next_words = self.structure[lead_in]
            except KeyError:
                # TODO backtracking?
                print('RAN INTO DEAD-END')
                break
            # get some extra randomness
            random.shuffle(next_words)
            s.append(random.choice(next_words))
        return s

def test()
  m = Markov_gen(4)
  data = open("input.txt").read()
  
  # We split by spaces, so clean up the data a bit.
  # remove more than one space
  data = re.sub("[ ]+", " ", data)
  # remove newlines not ending a sentence
  data = re.sub("(?<!\.)\n", " ", data)
  # remove multiple newline
  data = re.sub("\n+", "\n", data)
  # put space before and after certain characters (treat newline etc. as a "word")
  data = re.sub(r'([\n\.\t\?!\"])', r" \1 ", data)
  # remove more than one space. Redundant?
  data = re.sub(" +", " ", data)

  m.add_text(data)
  result = ' '.join(m.generate(50000))

  # remove extra space before these characters
  result = re.sub(r' ([\n\.\t\?!\"])', r"\1", result)
  # remove extra space after this character
  result = re.sub(r'([^ ]\") ', r"\1", result)
  print(result)
