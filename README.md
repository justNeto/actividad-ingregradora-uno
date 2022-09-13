# Partial project

## Usage
The solution binary uses previously generated files by adding them after the program or generates them at the moment by using the -s , --simulation flags:

```
# Using previously generated files
runProject -f file1 file2 file3 -p pattern1 pattern2

# Generating them at the moment. If transmission1.txt, transmission2.txt, transmission3.txt, mcode1.txt, mcode2.txt file exist in directory they will be overwritten.
runProject -s
```

BUGS:
When I tested it, could not name project binary the same as firstProject.
