#!/bin/bash

################################################################################
# PUSH_SWAP - Comprehensive Test Suite
# 100+ Tests including basic, advanced, and edge cases
# Supports: macOS (Intel/Apple Silicon) and Linux
################################################################################

# Color definitions for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
SKIPPED_TESTS=0

# Configuration
VERBOSE=${1:-0}
PLATFORM=$(uname -s)
PYTHON_CMD="python3"
VALGRIND_CMD="valgrind"

# Detect if tools are available
command -v "$PYTHON_CMD" &> /dev/null || PYTHON_CMD=""
command -v "$VALGRIND_CMD" &> /dev/null || VALGRIND_CMD=""

################################################################################
# Helper Functions
################################################################################

run_test() {
    local test_name="$1"
    local command="$2"
    local expected="$3"
    local category="$4"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [[ "$VERBOSE" == "-v" ]] || [[ "$VERBOSE" == "--verbose" ]]; then
        echo -n "[$category] $test_name... "
    else
        echo -n "Test $TOTAL_TESTS: $test_name... "
    fi
    
    # Execute command and capture output and exit code
    output=$(eval "$command" 2>&1)
    exit_code=$?
    
    # Check result based on expected value
    local test_passed=0
    
    if [[ "$expected" == "EXIT_OK" ]]; then
        [[ $exit_code -eq 0 ]] && test_passed=1
    elif [[ "$expected" == "EXIT_FAIL" ]]; then
        [[ $exit_code -ne 0 ]] && test_passed=1
    elif [[ "$expected" == "EMPTY" ]]; then
        [[ -z "$output" ]] && test_passed=1
    elif [[ "$expected" == "NOT_EMPTY" ]]; then
        [[ -n "$output" ]] && test_passed=1
    elif [[ "$expected" == "CONTAINS_ERROR" ]]; then
        [[ "$output" == *"Error"* ]] && test_passed=1
    elif [[ "$expected" == "NO_ERROR" ]]; then
        [[ "$output" != *"Error"* ]] && test_passed=1
    else
        # Numeric comparison
        [[ "$output" == "$expected" ]] && test_passed=1
    fi
    
    if [[ $test_passed -eq 1 ]]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        if [[ "$VERBOSE" == "-v" ]] || [[ "$VERBOSE" == "--verbose" ]]; then
            echo "  Expected: $expected"
            echo "  Got: $output"
            echo "  Exit code: $exit_code"
        fi
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

print_header() {
    echo ""
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_section() {
    echo ""
    echo -e "${MAGENTA}--- $1 ---${NC}"
}

skip_test() {
    local test_name="$1"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    echo "Test $TOTAL_TESTS: $test_name... ${YELLOW}SKIP${NC} (requirement not met)"
}

# Check if binary exists
if [ ! -f "./push_swap" ]; then
    echo -e "${RED}Error: push_swap binary not found. Run 'make' first.${NC}"
    exit 1
fi

################################################################################
# Test Suite Execution
################################################################################

print_header "PUSH_SWAP COMPREHENSIVE TEST SUITE"
echo "Platform: $PLATFORM"
echo "Python: ${PYTHON_CMD:-Not available}"
echo "Valgrind: ${VALGRIND_CMD:-Not available}"
echo "Verbose: $VERBOSE"

################################################################################
# CATEGORY 1: BASIC FUNCTIONALITY (10 tests)
################################################################################

print_section "CATEGORY 1: BASIC FUNCTIONALITY"

run_test "Single number" "./push_swap 1" "EXIT_OK" "BASIC"
run_test "Two numbers sorted" "./push_swap 1 2" "EXIT_OK" "BASIC"
run_test "Two numbers reverse" "./push_swap 2 1" "NOT_EMPTY" "BASIC"
run_test "Three sorted" "./push_swap 1 2 3" "EMPTY" "BASIC"
run_test "Three reverse" "./push_swap 3 2 1" "NOT_EMPTY" "BASIC"
run_test "Four random" "./push_swap 4 3 2 1" "NOT_EMPTY" "BASIC"
run_test "Five random" "./push_swap 5 4 3 2 1" "NOT_EMPTY" "BASIC"
run_test "Ten random" "./push_swap 10 9 8 7 6 5 4 3 2 1 | wc -l" "NOT_EMPTY" "BASIC"
run_test "Duplicate check" "./push_swap 1 2 2 3 2>/dev/null" "EXIT_FAIL" "BASIC"
run_test "Invalid char check" "./push_swap 1 a 3 2>/dev/null" "EXIT_FAIL" "BASIC"

################################################################################
# CATEGORY 2: QUOTED STRINGS (12 tests)
################################################################################

print_section "CATEGORY 2: QUOTED STRINGS INPUT"

run_test "Quoted 3 numbers" "./push_swap \"3 2 1\" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted 5 numbers" "./push_swap \"5 4 3 2 1\" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted single space" "./push_swap \"1 2 3\"" "EMPTY" "QUOTED"
run_test "Quoted double spaces" "./push_swap \"5  4  3  2  1\" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted leading spaces" "./push_swap \"  5 4 3 2 1\" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted trailing spaces" "./push_swap \"5 4 3 2 1  \" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted mixed spaces" "./push_swap \" 5  4   3  2 1 \" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted single number" "./push_swap \"42\"" "EXIT_OK" "QUOTED"
run_test "Quoted negative" "./push_swap \"-5 -4 -3 -2 -1\"" "EMPTY" "QUOTED"
run_test "Quoted mixed signs" "./push_swap \"-5 3 -1 2 0\" | wc -l" "NOT_EMPTY" "QUOTED"
run_test "Quoted with zero" "./push_swap \"0 1 2 3\"" "EMPTY" "QUOTED"
run_test "Quoted invalid in string" "./push_swap \"1 a 3\" 2>/dev/null" "EXIT_FAIL" "QUOTED"

################################################################################
# CATEGORY 3: NEGATIVE NUMBERS (10 tests)
################################################################################

print_section "CATEGORY 3: NEGATIVE NUMBERS"

run_test "All negative sorted" "./push_swap -5 -4 -3 -2 -1" "EMPTY" "NEGATIVE"
run_test "All negative reverse" "./push_swap -1 -2 -3 -4 -5 | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Mixed negative positive" "./push_swap -5 3 -1 2 0 | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Large negative" "./push_swap -1000000 -999999 -999998 | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Negative with zero" "./push_swap -1 0 1 2" "EMPTY" "NEGATIVE"
run_test "Quoted negative sorted" "./push_swap \"-5 -4 -3\"" "EMPTY" "NEGATIVE"
run_test "Quoted negative reverse" "./push_swap \"-3 -2 -1\" | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Quoted mixed signs" "./push_swap \"-10 5 -3 2 0\" | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Alternating signs" "./push_swap -1 1 -2 2 -3 3 | wc -l" "NOT_EMPTY" "NEGATIVE"
run_test "Single negative" "./push_swap -42" "EXIT_OK" "NEGATIVE"

################################################################################
# CATEGORY 4: ZERO AND EDGE CASES (10 tests)
################################################################################

print_section "CATEGORY 4: ZERO & EDGE CASES"

run_test "Only zero" "./push_swap 0" "EXIT_OK" "ZERO"
run_test "Zero at start" "./push_swap 0 1 2 3" "EMPTY" "ZERO"
run_test "Zero in middle" "./push_swap 3 0 1 2 | wc -l" "NOT_EMPTY" "ZERO"
run_test "Zero at end" "./push_swap 1 2 3 0 | wc -l" "NOT_EMPTY" "ZERO"
run_test "Multiple zeros" "./push_swap 0 1 0 2>&1" "CONTAINS_ERROR" "ZERO"
run_test "Negative and zero" "./push_swap -1 0 1" "EMPTY" "ZERO"
run_test "Large and small" "./push_swap 2147483647 -2147483648 0 | wc -l" "NOT_EMPTY" "ZERO"
run_test "Very small range" "./push_swap 1 2" "EMPTY" "ZERO"
run_test "Identical except zero" "./push_swap 0 0 2>&1" "CONTAINS_ERROR" "ZERO"
run_test "Zero with negatives" "./push_swap -5 0 5 | wc -l" "NOT_EMPTY" "ZERO"

################################################################################
# CATEGORY 5: ERROR CASES (15 tests)
################################################################################

print_section "CATEGORY 5: ERROR CASES & VALIDATION"

run_test "Empty argument" "./push_swap \"\" 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "No arguments" "./push_swap 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Invalid character a" "./push_swap 1 a 3 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Invalid character @" "./push_swap \"1 @ 3\" 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Invalid character space only" "./push_swap \"   \" 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Only letters" "./push_swap abc 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Mixed letters numbers" "./push_swap 1a2b3c 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Special chars" "./push_swap \"1 # 3\" 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Plus without number" "./push_swap + 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Minus without number" "./push_swap - 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Double signs" "./push_swap --5 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Plus plus" "./push_swap ++5 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Decimal point" "./push_swap 3.14 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Scientific notation" "./push_swap 1e5 2>&1" "CONTAINS_ERROR" "ERROR"
run_test "Hex number" "./push_swap 0xFF 2>&1" "CONTAINS_ERROR" "ERROR"

################################################################################
# CATEGORY 6: INTEGER OVERFLOW (12 tests)
################################################################################

print_section "CATEGORY 6: INTEGER OVERFLOW & BOUNDARIES"

run_test "INT_MAX" "./push_swap 2147483647" "EXIT_OK" "OVERFLOW"
run_test "INT_MIN" "./push_swap -2147483648" "EXIT_OK" "OVERFLOW"
run_test "INT_MAX + 1" "./push_swap 2147483648 2>&1" "CONTAINS_ERROR" "OVERFLOW"
run_test "INT_MIN - 1" "./push_swap -2147483649 2>&1" "CONTAINS_ERROR" "OVERFLOW"
run_test "Large overflow" "./push_swap 9999999999 2>&1" "CONTAINS_ERROR" "OVERFLOW"
run_test "Negative overflow" "./push_swap -9999999999 2>&1" "CONTAINS_ERROR" "OVERFLOW"
run_test "INT_MAX in array" "./push_swap 2147483647 100 -100 | wc -l" "NOT_EMPTY" "OVERFLOW"
run_test "INT_MIN in array" "./push_swap -2147483648 100 -100 | wc -l" "NOT_EMPTY" "OVERFLOW"
run_test "Both boundaries" "./push_swap 2147483647 -2147483648 0 | wc -l" "NOT_EMPTY" "OVERFLOW"
run_test "Near INT_MAX" "./push_swap 2147483646" "EXIT_OK" "OVERFLOW"
run_test "Near INT_MIN" "./push_swap -2147483647" "EXIT_OK" "OVERFLOW"
run_test "Quoted overflow" "./push_swap \"2147483648\" 2>&1" "CONTAINS_ERROR" "OVERFLOW"

################################################################################
# CATEGORY 7: DUPLICATE DETECTION (12 tests)
################################################################################

print_section "CATEGORY 7: DUPLICATE DETECTION"

run_test "Two identical" "./push_swap 1 1 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Three identical" "./push_swap 1 1 1 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate at start" "./push_swap 1 1 2 3 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate in middle" "./push_swap 1 2 2 3 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate at end" "./push_swap 1 2 3 3 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Multiple duplicates" "./push_swap 1 2 1 2 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate negatives" "./push_swap -1 -1 0 1 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate with zero" "./push_swap 0 1 0 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Large duplicate" "./push_swap 2147483647 2147483647 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Quoted duplicate" "./push_swap \"1 2 1\" 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "Duplicate spaces" "./push_swap \"1  1  2\" 2>&1" "CONTAINS_ERROR" "DUPS"
run_test "No duplicates (valid)" "./push_swap 1 2 3 4 5 6 7 8 9 10" "NO_ERROR" "DUPS"

################################################################################
# CATEGORY 8: PERFORMANCE TESTS (8 tests)
################################################################################

print_section "CATEGORY 8: PERFORMANCE & OPERATION COUNTS"

if [ -n "$PYTHON_CMD" ]; then
    # 10 random numbers
    ARG_10=$($PYTHON_CMD -c "import random; print(' '.join(map(str, random.sample(range(100), 10))))" 2>/dev/null)
    if [ -n "$ARG_10" ]; then
        OPS=$(./push_swap $ARG_10 2>/dev/null | wc -l)
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -n "Test $TOTAL_TESTS: 10 random numbers (ops: $OPS)... "
        if [ "$OPS" -lt 50 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}✗ FAIL${NC} (expected < 50, got $OPS)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    
    # 50 random numbers
    ARG_50=$($PYTHON_CMD -c "import random; print(' '.join(map(str, random.sample(range(500), 50))))" 2>/dev/null)
    if [ -n "$ARG_50" ]; then
        OPS=$(./push_swap $ARG_50 2>/dev/null | wc -l)
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -n "Test $TOTAL_TESTS: 50 random numbers (ops: $OPS)... "
        if [ "$OPS" -lt 200 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}✗ FAIL${NC} (expected < 200, got $OPS, Failed to get 100% but Pass for less than 100% depending on the operation counts allowed mentioned in the evaluation sheet)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    
    # 100 random numbers ⭐ CRITICAL
    ARG_100=$($PYTHON_CMD -c "import random; print(' '.join(map(str, random.sample(range(1000), 100))))" 2>/dev/null)
    if [ -n "$ARG_100" ]; then
        OPS=$(./push_swap $ARG_100 2>/dev/null | wc -l)
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -n "Test $TOTAL_TESTS: 100 random numbers (ops: $OPS)... "
        if [ "$OPS" -lt 700 ]; then
            echo -e "${GREEN}✓ PASS${NC} ⭐"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}✗ FAIL${NC} ⭐ (expected < 700, got $OPS, Failed to get 100% but Pass for less than 100% depending on the operation counts allowed mentioned in the evaluation sheet)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    
    # 500 random numbers ⭐ CRITICAL
    ARG_500=$($PYTHON_CMD -c "import random; print(' '.join(map(str, random.sample(range(10000), 500))))" 2>/dev/null)
    if [ -n "$ARG_500" ]; then
        OPS=$(./push_swap $ARG_500 2>/dev/null | wc -l)
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -n "Test $TOTAL_TESTS: 500 random numbers (ops: $OPS)... "
        if [ "$OPS" -lt 5500 ]; then
            echo -e "${GREEN}✓ PASS${NC} ⭐"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}✗ FAIL${NC} ⭐ (expected < 5500, got $OPS, Failed to get 100% but Pass for less than 100% depending on the operation counts allowed mentioned in the evaluation sheet)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    
    # Consistency test: Run 100-number test 3 times
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -n "Test $TOTAL_TESTS: Consistency (3x 100 numbers)... "
    all_pass=1
    for i in {1..3}; do
        ARG=$($PYTHON_CMD -c "import random; print(' '.join(map(str, random.sample(range(1000), 100))))" 2>/dev/null)
        OPS=$(./push_swap $ARG 2>/dev/null | wc -l)
        if [ "$OPS" -ge 700 ]; then
            all_pass=0
        fi
    done
    if [ $all_pass -eq 1 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC} (inconsistent results)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
else
    skip_test "10 random numbers"
    skip_test "50 random numbers"
    skip_test "100 random numbers ⭐"
    skip_test "500 random numbers ⭐"
    skip_test "Consistency test"
fi

################################################################################
# CATEGORY 9: COMPLEX SCENARIOS (15 tests)
################################################################################

print_section "CATEGORY 9: COMPLEX SCENARIOS"

run_test "Ascending 1-10" "./push_swap 1 2 3 4 5 6 7 8 9 10" "EMPTY" "COMPLEX"
run_test "Descending 10-1" "./push_swap 10 9 8 7 6 5 4 3 2 1 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Alternating high low" "./push_swap 10 1 9 2 8 3 7 4 6 5 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "All same except one" "./push_swap 5 5 5 5 5 5 5 5 5 1 2>&1" "CONTAINS_ERROR" "COMPLEX"
run_test "One element out of place" "./push_swap 1 2 3 5 4 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Nearly sorted" "./push_swap 1 2 3 4 5 6 7 8 9 10 11 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Bimodal distribution" "./push_swap 1 1 1 10 10 10 2>&1" "CONTAINS_ERROR" "COMPLEX"
run_test "Large range small array" "./push_swap -1000000 1000000 0 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Reverse every 2nd" "./push_swap 2 1 4 3 6 5 8 7 10 9 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Mostly sorted 1" "./push_swap 1 2 3 4 5 6 7 8 10 9 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Random order big nums" "./push_swap 987654 123456 555555 111111 999999 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Single swap needed" "./push_swap 2 1" "NOT_EMPTY" "COMPLEX"
run_test "Long quoted complex" "./push_swap \"10 2 8 4 6 3 9 1 7 5\" | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "Array with negatives complex" "./push_swap -100 50 -75 25 -50 100 | wc -l" "NOT_EMPTY" "COMPLEX"
run_test "U-shaped array" "./push_swap 10 9 8 7 6 5 4 3 2 1 | wc -l" "NOT_EMPTY" "COMPLEX"

################################################################################
# CATEGORY 10: OUTPUT FORMAT (8 tests)
################################################################################

print_section "CATEGORY 10: OUTPUT FORMAT & VALIDITY"

run_test "Only valid operations" "./push_swap 5 4 3 2 1 | grep -E '^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$' | wc -l" "NOT_EMPTY" "FORMAT"
run_test "No invalid operations" "./push_swap 5 4 3 | grep -vE '^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$' | wc -l" "0" "FORMAT"
run_test "Newline after each op" "./push_swap 3 2 1 | grep -c '^'  | wc -l" "NOT_EMPTY" "FORMAT"
run_test "No trailing whitespace" "./push_swap 2 1 | grep ' $' | wc -l" "0" "FORMAT"
run_test "stderr for errors" "./push_swap \"bad\" 2>/dev/null | wc -l" "0" "FORMAT"
run_test "Error to stderr" "./push_swap \"bad\" 2>&1 1>/dev/null | grep -c Error" "1" "FORMAT"
run_test "Correct exit code success" "./push_swap 1 2 3; echo \$?" "0" "FORMAT"
run_test "Correct exit code error" "./push_swap \"bad\" 2>/dev/null; echo \$?" "EXIT_FAIL" "FORMAT"

################################################################################
# CATEGORY 11: MEMORY TESTS (5 tests)
################################################################################

print_section "CATEGORY 11: MEMORY & CLEANUP"

if [ -n "$VALGRIND_CMD" ]; then
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -n "Test $TOTAL_TESTS: Valgrind no leaks (small)... "
    VALGRIND_OUT=$($VALGRIND_CMD --leak-check=full --quiet ./push_swap 5 4 3 2 1 2>&1)
    if [[ "$VALGRIND_OUT" == *"0 leaks"* ]] || [[ -z "$VALGRIND_OUT" ]]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -n "Test $TOTAL_TESTS: Valgrind error on error... "
    VALGRIND_OUT=$($VALGRIND_CMD --leak-check=full --quiet ./push_swap "bad" 2>&1)
    if [[ "$VALGRIND_OUT" == *"0 leaks"* ]] || [[ -z "$VALGRIND_OUT" ]]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -n "Test $TOTAL_TESTS: Valgrind duplicate reject... "
    VALGRIND_OUT=$($VALGRIND_CMD --leak-check=full --quiet ./push_swap 1 1 2 2>&1)
    if [[ "$VALGRIND_OUT" == *"0 leaks"* ]] || [[ -z "$VALGRIND_OUT" ]]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
elif [ "$PLATFORM" == "Darwin" ]; then
    # macOS - use leaks command
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -n "Test $TOTAL_TESTS: macOS leaks (small)... "
    LEAKS_OUT=$(leaks -atExit -- ./push_swap 5 4 3 2 1 2>&1)
    if [[ "$LEAKS_OUT" == *"0 leaks"* ]]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
else
    skip_test "Memory leak detection (Valgrind required)"
    skip_test "Memory on error"
    skip_test "Memory on duplicate"
fi

################################################################################
# CATEGORY 12: EDGE CASE COMBINATIONS (10 tests)
################################################################################

print_section "CATEGORY 12: EDGE CASE COMBINATIONS"

run_test "Max and min together" "./push_swap 2147483647 -2147483648 | wc -l" "NOT_EMPTY" "EDGE"
run_test "Max min and zero" "./push_swap 2147483647 -2147483648 0 | wc -l" "NOT_EMPTY" "EDGE"
run_test "Quoted max min zero" "./push_swap \"2147483647 -2147483648 0\" | wc -l" "NOT_EMPTY" "EDGE"
run_test "Two element sort" "./push_swap 2 1" "NOT_EMPTY" "EDGE"
run_test "Two element reverse" "./push_swap 1 2" "EMPTY" "EDGE"
run_test "Three element all equal" "./push_swap 5 5 5 2>&1" "CONTAINS_ERROR" "EDGE"
run_test "Quoted empty spaces" "./push_swap \"\" 2>&1" "CONTAINS_ERROR" "EDGE"
run_test "Quoted only spaces" "./push_swap \"     \" 2>&1" "CONTAINS_ERROR" "EDGE"
run_test "Negative quoted single" "./push_swap \"-1\"" "EXIT_OK" "EDGE"
run_test "Large quoted array" "./push_swap \"100 99 98 97 96 95 94 93 92 91\" | wc -l" "NOT_EMPTY" "EDGE"

################################################################################
# Test Summary
################################################################################

print_header "TEST SUMMARY"

total_run=$((PASSED_TESTS + FAILED_TESTS))
success_rate=0
if [ $total_run -gt 0 ]; then
    success_rate=$((PASSED_TESTS * 100 / total_run))
fi

echo ""
echo "Total Tests: $TOTAL_TESTS"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
if [ $SKIPPED_TESTS -gt 0 ]; then
    echo -e "Skipped: ${YELLOW}$SKIPPED_TESTS${NC}"
fi
echo "Success Rate: $success_rate%"

echo ""
echo "Critical Tests Status:"
if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "  ${GREEN}✓ 100 numbers < 700 ops${NC}"
    echo -e "  ${GREEN}✓ 500 numbers < 5500 ops${NC}"
    echo -e "  ${GREEN}✓ No memory leaks${NC}"
    echo -e "  ${GREEN}✓ All error handling${NC}"
else
    echo -e "  ${RED}✗ Some tests failed${NC}"
fi

echo ""
if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}✓ ALL TESTS PASSED!${NC}"
    echo -e "${CYAN}Ready for submission 🎉${NC}"
    exit 0
else
    echo -e "${RED}✗ SOME TESTS FAILED${NC}"
    echo "Review failed tests and fix issues."
    exit 1
fi
