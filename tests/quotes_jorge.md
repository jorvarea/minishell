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


### echo

## Test Case 1
**Command:**
echo hola

**Expected Output:**
hola\n

## Test Case 2
**Command:**
echo -n hola

**Expected Output:**
hola

## Test Case 3
**Command:**
echo -nnnnnnn hola

**Expected Output:**
hola

## Test Case 4
**Command:**
echo -n -n -n hola

**Expected Output:**
hola

## Test Case 5
**Command:**
echo -nvcfyjh hola

**Expected Output:**
-nvcfyjh hola\n

## Test Case 6
**Command:**
echo -n -nvcfyjh hola

**Expected Output:**
-nvcfyjh hola

## Test Case 7
**Command:**
echo hola adios pedro por su casa

**Expected Output:**
echo hola adios pedro por su casa\n

---

### pwd

## Test Case 1
**Command:**
pwd

**Expected Output:**
/Users/jorvarea/

## Test Case 2
**Command:**
pwd ftyh fhgj

**Expected Output:**
/Users/jorvarea

## Test Case 3
**Command:**
pwd bgyhb -m

**Expected Output:**
/Users/jorvarea

## Test Case 4
**Command:**
pwd -asf

**Expected Output:**
-minishell: pwd: -a: invalid option
pwd: usage: pwd