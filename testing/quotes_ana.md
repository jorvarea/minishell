# Bash Quoting and Command Combination Tests by Ana

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


## Simple Quotes

### Test Case 1: Single Quotes Inside Single Quotes
**Command:**
(Insert single quotes inside single quotes command here)

**Expected Output:**
(Insert expected output here)

**Minishell Output:** (✅ Pass / ❌ KO)
(Insert actual output here)

---

## Double Quotes

### Test Case 1: Double Quotes Inside Single Quotes
**Command:**
(Insert double quotes inside single quotes command here)

**Expected Output:**
(Insert expected output here)

**Minishell Output:** (✅ Pass / ❌ KO)
(Insert actual output here)

---

## Nested Quotes

### Test Case 1: Nested Single and Double Quotes
**Command:**
(Insert nested single and double quotes command here)

**Expected Output:**
(Insert expected output here)

**Minishell Output:** (✅ Pass / ❌ KO)
(Insert actual output here)

---

## Escaped Quotes

### Test Case 1: Escaped Single Quotes
**Command:**
(Insert escaped single quotes command here)

**Expected Output:**
(Insert expected output here)

**Minishell Output:** (✅ Pass / ❌ KO)
(Insert actual output here)

---

## Combination of Quotes and Commands

### Test Case 1: Quotes in Command Substitution
**Command:**
(Insert quotes in command substitution command here)

**Expected Output:**
(Insert expected output here)

**Minishell Output:** (✅ Pass / ❌ KO)
(Insert actual output here)

---