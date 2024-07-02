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

---

## export

### Test Case 1
**Command:**
```bash
export
```
**Expected Output:**
```bash
declare -x DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/1000/bus"
declare -x HOME="/home/jorvarea"
...
...
```

**Minishell Output:** ✅ OK
```bash
declare -x PWD="/Users/jorvarea/Desktop/cursus/minishell"
declare -x NVM_RC_VERSION="(null)"
...
...
```

### Test Case 2
**Command:**
```bash
export key=value
```
**Expected Output:**
```bash
```
(variable added to env)

**Minishell Output:** ✅ OK
```bash
```
(variable added to env)

### Test Case 3
**Command:**
```bash
export 9tor=tor
```
**Expected Output:**
```bash
-bash: export: `9tor=tor': not a valid identifier
```

**Minishell Output:** ✅ OK
```bash
-minishell: export: `9tor=tor': not a valid identifier
```

### Test Case 4
**Command:**
```bash
export _tor=tor
```
**Expected Output:**
```bash
```
(variable added to env)

**Minishell Output:** ✅ OK
```bash
```
(variable added to env)

### Test Case 5
**Command:**
```bash
export t0r=tor
```
**Expected Output:**
```bash
```
(variable added to env)

**Minishell Output:** ✅ OK
```bash
```
(variable added to env)

### Test Case 6
**Command:**
```bash
export t@r=tor
```
**Expected Output:**
```bash
-bash: export: 't@r=tor': not a valid identifier
```

**Minishell Output:** ✅ OK
```bash
-minishell: export: 't@r=tor': not a valid identifier
```

### Test Case 7
**Command:**
```bash
export -y ana=cast
```

**Expected Output:**
```bash
-bash: export: -y: invalid option
export: usage: export [-fn] [name[=value] ...] or export -p
```
(variable not added to env)

**Minishell Output:** ✅ OK
```bash
-minishell: export: -y: invalid option
export: usage: export [name[=value] ...]
```
(variable not added to env)

### Test Case 8
**Command:**
```bash
export jor=varea -k
```

**Expected Output:**
```bash
-bash: export: `-k': not a valid identifier
```
(variable added to env)

**Minishell Output:** ✅ OK
```bash
-minishell: export: '-k': not a valid identifier
```
(variable added to env)

### Test Case 9
**Command:**
```bash
export ana=cast
export ana=varea
env
```

**Expected Output:**
```bash
...
ana=varea
```

**Minishell Output:** ✅ OK
```bash
...
ana=varea
```

### Test Case 10
**Command:**
```bash
export hola=adios=buenos_dias
```
**Expected Output:**
```bash
```
(variable added to env as key: hola, value: adios=buenos_dias)

**Minishell Output:** ✅ OK
```bash
```
(variable added to env as key: hola, value: adios=buenos_dias)

---

## cd

### Test Case 1
**Command:**
```bash
cd ..
pwd
env
```

**Expected Output:**
```bash
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus
OLDPWD=/Users/jorvarea/Desktop/cursus/minishell
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus
OLDPWD=/Users/jorvarea/Desktop/cursus/minishell
```

### Test Case 2
**Command:**
```bash
cd ..
pwd
cd -
env
```

**Expected Output:**
```bash
/Users/jorvarea/Desktop
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus
OLDPWD=/Users/jorvarea/Desktop
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/Desktop
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus
OLDPWD=/Users/jorvarea/Desktop
```

### Test Case 3
**Command:**
```bash
cd ~
pwd
env
```

**Expected Output:**
```bash
/Users/jorvarea
...
PWD=/Users/jorvarea
OLDPWD=/Users/jorvarea/Desktop/cursus
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea
...
PWD=/Users/jorvarea
OLDPWD=/Users/jorvarea/Desktop/cursus
```

### Test Case 4
**Command:**
```bash
cd ghj
```

**Expected Output:**
```bash
-bash: cd: ghj: No such file or directory
```

**Minishell Output:** ✅ OK
```bash
-minishell: chdir: No such file or directory
```

### Test Case 5
**Command:**
```bash
cd -u
```

**Expected Output:**
```bash
-bash: cd: -u: invalid option
cd: usage: cd [-L|[-P [-e]] [-@]] [dir]
```

**Minishell Output:** ✅ OK
```bash
-minishell: cd: -u: invalid option
cd: usage: cd [dir]
```

### Test Case 6
**Command:**
```bash
pwd
cd minishell/
env
```

**Expected Output:**
```bash
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus/minishell
OLDPWD=/Users/jorvarea/Desktop/cursus
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus/minishell
OLDPWD=/Users/jorvarea/Desktop/cursus
```

### Test Case 7
**Command:**
```bash
cd minishell/ fghj
pwd
```

**Expected Output:**
```bash
-minishell: cd: too many arguments
/Users/jorvarea/Desktop/cursus
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/Desktop/cursus
...
PWD=/Users/jorvarea/Desktop/cursus/minishell
OLDPWD=/Users/jorvarea/Desktop/cursus
```

### Test Case 8
**Command:**
```bash
cd .DS_Store
pwd
```

**Expected Output:**
```bash
-bash: cd: .DS_Store: Not a directory
```

**Minishell Output:** ✅ OK
```bash
-minishell: chdir: .DS_Store: Not a directory
```

---

## exit

### Test Case 1
**Command:**
```bash
exit ghj
```

**Expected Output:**
```bash
-bash: exit: ghj: numeric argument required
```

**Minishell Output:** ✅ OK
```bash
-minishell: exit: too many arguments
```

### Test Case 2
**Command:**
```bash
exit
```

**Expected Output:**
```bash
```

**Minishell Output:** ✅ OK
```bash
```

---

## unset

### Test Case 1
**Command:**
```bash
unset
```

**Expected Output:**
```bash
```

**Minishell Output:** ✅ OK
```bash
```

### Test Case 2
**Command:**
```bash
unset ghj
```

**Expected Output:**
```bash
```

**Minishell Output:** ✅ OK
```bash
```

### Test Case 3
**Command:**
```bash
unset -j
```

**Expected Output:**
```bash
-bash: unset: -j: invalid option
unset: usage: unset [-f] [-v] [-n] [name ...]
```

**Minishell Output:** ✅ OK
```bash
-minishell: unset: -j: invalid option
unset: usage: unset [name ...]
```

### Test Case 4
**Command:**
```bash
unset -j
```

**Expected Output:**
```bash
-bash: unset: -j: invalid option
unset: usage: unset [-f] [-v] [-n] [name ...]
```

**Minishell Output:** ✅ OK
```bash
-minishell: unset: -j: invalid option
unset: usage: unset [name ...]
```

### Test Case 5
**Command:**
```bash
export hola=adios
unset hola
env
```

**Expected Output:**
```bash
...
```
(hola doesn't appear in the env output)

**Minishell Output:** ✅ OK
```bash
...
```
(hola doesn't appear in the env output)

---

## executable

### Test Case 1
**Command:**
```bash
hola
```

**Expected Output:**
```bash
-bash: hola: command not found
```
(hola doesn't appear in the env output)

**Minishell Output:** ✅ OK
```bash
-minishell: hola: command not found
```

### Test Case 2
**Command:**
```bash
ls
```

**Expected Output:**
```bash
LICENSE   Makefile  README.md docs      include   leaks.sh  lib       minishell src       tests
```
(hola doesn't appear in the env output)

**Minishell Output:** ✅ OK
```bash
LICENSE         Makefile        README.md       docs            include         leaks.sh        lib             minishell       src             tests
```

### Test Case 3
**Command:**
```bash
./hello_world.sh
```

**Expected Output:**
```bash
hello_world
```

**Minishell Output:** ✅ OK
```bash
hello_world
```

---

## expanding ~

### Test Case 1
**Command:**
```bash
echo ~
```

**Expected Output:**
```bash
/home/jorvarea
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea
```

### Test Case 2
**Command:**
```bash
echo ~/directory
```

**Expected Output:**
```bash
/home/jorvarea/directory
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea/directory
```

### Test Case 3
**Command:**
```bash
echo "~"
```

**Expected Output:**
```bash
~
```

**Minishell Output:**  ❌ FAIL
```bash
"~"
```

### Test Case 4
**Command:**
```bash
echo ~e
```

**Expected Output:**
```bash
~e
```

**Minishell Output:**  ✅ OK
```bash
~e
```

### Test Case 5
**Command:**
```bash
echo /hola/~/adios
```

**Expected Output:**
```bash
/hola/~/adios
```

**Minishell Output:**  ✅ OK
```bash
/hola/~/adios
```

---

## Expand enviroment variables

### Test Case 1
**Command:**
```bash
echo $HOME
echo $PWD
export hola=adios
echo $hola
```

**Expected Output:**
```bash
/Users/jorvarea
/Users/jorvarea/Desktop/cursus/minishell
adios
```

**Minishell Output:** ✅ OK
```bash
/Users/jorvarea
/Users/jorvarea/Desktop/cursus/minishell
adios
```

### Test Case 2
**Command:**
```bash
echo '$HOME'
```

**Expected Output:**
```bash
$HOME
```

**Minishell Output:** ✅ OK
```bash
$HOME
```

### Test Case 3
**Command:**
```bash
echo hola$?adios
```

**Expected Output:**
```bash
hola0adios
```

**Minishell Output:** ✅ OK
```bash
hola0adios
```

### Test Case 4
**Command:**
```bash
echo $?$?
```

**Expected Output:**
```bash
00
```

**Minishell Output:** ✅ OK
```bash
00
```

### Test Case 5
**Command:**
```bash
echo $? + $?
```

**Expected Output:**
```bash
0 + 0
```

**Minishell Output:** ✅ OK
```bash
0 + 0
```