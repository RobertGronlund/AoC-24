# Day-5
with open('day-5/input.txt', 'r') as file:
    rules = []
    updates = []

    # Read the entire file and split into two sectors
    content = file.read().strip().split('\n\n')
    sector1 = content[0].strip().split('\n')
    sector2 = content[1].strip().split('\n')

    # Process the first sector
    for line in sector1:
        numbers = list(map(int, line.strip().split('|')))
        rules.append(numbers)

    # Process the second sector
    for line in sector2:
        numbers = list(map(int, line.strip().split(',')))
        updates.append(numbers)


# Part-1
def is_b_before_a(upd, rulz):
    try:
        index_a = upd.index(rulz[0])
        index_b = upd.index(rulz[1])
        return index_a > index_b
    except ValueError:
        # If either a or b is not in the list, return False
        return False

correct_medians = []
bad_updates = []
for update in updates:
    rule_breaker = False
    for rule in rules:
        if (is_b_before_a(update, rule)):
            rule_breaker = True
            bad_updates.append(update)
            break
    if not rule_breaker:
        correct_medians.append(update[len(update) // 2])

print("Correct Medians:", correct_medians)
print("Sum of Correct Medians:", sum(correct_medians))

# Day-5
def index_switcher(upd, rulz):
    index_a = upd.index(rulz[0])
    index_b = upd.index(rulz[1])
    upd[index_a], upd[index_b] = upd[index_b], upd[index_a]

converted_updates_medians = []
i = 0
while i < len(bad_updates):
    update = bad_updates[i]
    rule_breaker = False
    for rule in rules:
        if is_b_before_a(update, rule):
            rule_breaker = True
            index_switcher(update, rule)
            break
    
    if not rule_breaker:
        i += 1  # Only increment the index if rule_breaker is False
        converted_updates_medians.append(update[len(update) // 2])

print("Converted Updates Medians:", converted_updates_medians)
print("Sum of Converted Updates Medians:", sum(converted_updates_medians))
