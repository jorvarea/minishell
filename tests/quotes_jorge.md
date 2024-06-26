# Bash Quoting and Command Combination Tests by Jorge

## Introduction

This document contains a series of tested cases that demonstrate the behavior of the Bash shell when using various combinations of commands and quotes (both single and double). Each test case includes the command executed, the expected output, and the actual output observed. These tests are designed to explore and document how Bash handles complex quoting scenarios, which can be helpful for debugging and understanding shell behavior.

## Table of Contents

1. [Test Structure Example](text-structure-example)
2. [Simple Quotes](#simple-quotes)
3. [Double Quotes](#double-quotes)
4. [Nested Quotes](#nested-quotes)
5. [Escaped Quotes](#escaped-quotes)
6. [Combination of Quotes and Commands](#combination-of-quotes-and-commands)

---

## Test Structure Example

### Test Case [N]: Single Quote inside Double Quotes
**Command:**
```bash
echo -e "It's a test"
```
**Expected Output:**
```bash
	It's a test
```

**Minishell Output:** ✅ OK
```bash
	It's a test
```

---

## echo

### Test Case 1: Simple Echo
**Command:**
```bash
echo hola
```
**Expected Output:**
```bash
hola\n
```

**Minishell Output:** ✅ OK
```bash
hola\n
```

### Test Case 2: No Newline with -n Option
**Command:**
```bash
echo -n hola
```
**Expected Output:**
```bash
hola
```

**Minishell Output:** ✅ OK
```bash
hola
```

### Test Case 3: Multiple -n Options Ignored
**Command:**
```bash
echo -nnnnnnn hola
```
**Expected Output:**
```bash
hola
```

**Minishell Output:** ✅ OK
```bash
hola
```

### Test Case 4: Multiple -n Options with Other Flags
**Command:**
```bash
echo -n -n -n hola
```
**Expected Output:**
```bash
hola
```

**Minishell Output:** ✅ OK
```bash
hola
```

### Test Case 5: Invalid Option with -n Flag
**Command:**
```bash
echo -nvcfyjh hola
```
**Expected Output:**
```bash
-nvcfyjh hola\n
```

**Minishell Output:** ✅ OK
```bash
-nvcfyjh hola\n
```

### Test Case 6: Invalid Option with -n Flag at Beginning
**Command:**
```bash
echo -n -nvcfyjh hola
```
**Expected Output:**
```bash
-nvcfyjh hola
```

**Minishell Output:** ✅ OK
```bash
-nvcfyjh hola
```

### Test Case 7: Multiple Arguments
**Command:**
```bash
echo hola adios pedro por su casa
```
**Expected Output:**
```bash
hola adios pedro por su casa\n
```

**Minishell Output:** ✅ OK
```bash
hola adios pedro por su casa\n
```

---

## pwd

### Test Case 1: Simple Pwd
**Command:**
```bash
pwd
```
**Expected Output:**
```bash
/Users/jorvarea/
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/
```

### Test Case 2: Pwd with Invalid Arguments
**Command:**
```bash
pwd ftyh fhgj
```
**Expected Output:**
```bash
/Users/jorvarea/
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/
```

### Test Case 3: Pwd with Invalid Option
**Command:**
```bash
pwd bgyhb -m
```
**Expected Output:**
```bash
/Users/jorvarea/
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/
```

### Test Case 4: Pwd with Invalid Flag
**Command:**
```bash
pwd -asf
```
**Expected Output:**
```bash
-bash: pwd: -a: invalid option
pwd: usage: pwd [-LP]
```

**Minishell Output:** ✅ OK
```bash
-minishell: pwd: -a: invalid option
pwd: usage: pwd
```

---


## env

### Test Case 1
**Command:**
```bash
env
```
**Expected Output:**
```bash
PWD=/Users/jorvarea/Desktop/cursus/minishell
...
```

**Minishell Output:** ✅ OK
```bash
PWD=/Users/jorvarea/Desktop/cursus/minishell
...
```

### Test Case 2
**Command:**
```bash
env vgjn
```
**Expected Output:**
```bash
env: ‘vgjn’: No such file or directory
```

**Minishell Output:** ✅ OK
```bash
env: too many arguments
```