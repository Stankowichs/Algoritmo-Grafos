#!/bin/bash

gawk  '{split($0, w); s=""; for(i=1; i<=asort(w); i++) s=s w[i] " "; print s }'  | sed 's/ $//' | sort -n
