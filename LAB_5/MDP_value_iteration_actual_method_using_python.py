import matplotlib.pyplot as plt
import numpy as np

eps = 1e-4
GAMMA = 0.9
grid = [[0, 0, 0, 1], [0, None, 0, -1], [0, 0, 0, 0]]
policy = [[None, None, None, None], [None, None, None, None], [None, None, None, None]]
actions = {0: "U⬆", 1: "D⬇", 2: "R➡", 3: "⬅ L"}


def is_valid_state(coordinate):
    x = coordinate[0]
    y = coordinate[1]
    if (x == 0 and y == 3) or (x == 1 and y == 3) or (x == 1 and y == 1):
        return False
    return True


def is_outside_or_wall(coordinate):
    x = coordinate[0]
    y = coordinate[1]
    if x == 1 and y == 1:
        return True
    elif x < 0 or y < 0 or x >= 3 or y >= 4:
        return True
    return False


def calculate_exp_val(state, action):
    value = 0.0
    p_deterministic = 0.8
    p_noise = 0.1
    x = state[0]
    y = state[1]
    if action == "U⬆":
        next_states = [[x - 1, y], [x, y + 1], [x, y - 1]]
        for i in range(len(next_states)):
            if i == 0:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_deterministic * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_deterministic * (GAMMA * grid[nx][ny]))
            else:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_noise * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_noise * (GAMMA * grid[nx][ny]))
    elif action == "D⬇":
        next_states = [[x + 1, y], [x, y + 1], [x, y - 1]]
        for i in range(len(next_states)):
            if i == 0:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_deterministic * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_deterministic * (GAMMA * grid[nx][ny]))
            else:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_noise * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_noise * (GAMMA * grid[nx][ny]))
    elif action == "R➡":
        next_states = [[x, y + 1], [x - 1, y], [x + 1, y]]
        for i in range(len(next_states)):
            if i == 0:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_deterministic * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_deterministic * (GAMMA * grid[nx][ny]))
            else:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_noise * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_noise * (GAMMA * grid[nx][ny]))
    elif action == "⬅ L":
        next_states = [[x, y - 1], [x - 1, y], [x + 1, y]]
        for i in range(len(next_states)):
            if i == 0:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_deterministic * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_deterministic * (GAMMA * grid[nx][ny]))
            else:
                if is_outside_or_wall([next_states[i][0], next_states[i][1]]):
                    value += (p_noise * (GAMMA * grid[x][y]))
                else:
                    nx = next_states[i][0]
                    ny = next_states[i][1]
                    value += (p_noise * (GAMMA * grid[nx][ny]))

    return value


def Value_Convergence(state):
    value = -1e9

    for i in range(4):
        action = actions[i]
        if action == "U⬆":
            exp_val_for_u = calculate_exp_val(state, action)
            if exp_val_for_u > value:
                value = exp_val_for_u

        elif action == "D⬇":
            exp_val_for_d = calculate_exp_val(state, action)
            if exp_val_for_d > value:
                value = exp_val_for_d

        elif action == "R➡":
            exp_val_for_r = calculate_exp_val(state, action)
            if exp_val_for_r > value:
                value = exp_val_for_r

        elif action == "⬅ L":
            exp_val_for_l = calculate_exp_val(state, action)
            if exp_val_for_l > value:
                value = exp_val_for_l

    return value


def Policy_Extraction(state):
    value = -1e9
    optimal_action = None
    for i in range(4):
        action = actions[i]
        if action == "U⬆":
            exp_val_for_u = calculate_exp_val(state, action)
            if exp_val_for_u > value:
                value = exp_val_for_u
                optimal_action = "U⬆"
        elif action == "D⬇":
            exp_val_for_d = calculate_exp_val(state, action)
            if exp_val_for_d > value:
                value = exp_val_for_d
                optimal_action = "D⬇"
        elif action == "R➡":
            exp_val_for_r = calculate_exp_val(state, action)
            if exp_val_for_r > value:
                value = exp_val_for_r
                optimal_action = "R➡"
        elif action == "⬅ L":
            exp_val_for_l = calculate_exp_val(state, action)
            if exp_val_for_l > value:
                value = exp_val_for_l
                optimal_action = "⬅ L"

    return optimal_action


if __name__ == '__main__':
    loop_breaker = 100

    # Loop through until value convergence
    while loop_breaker > eps:
        loop_breaker = 0
        for i in range(3):
            for j in range(4):
                if is_valid_state([i, j]):
                    value = Value_Convergence([i, j])
                    loop_breaker = max(loop_breaker, abs(value - grid[i][j]))
                    grid[i][j] = value

        # Policy Extraction
        for i in range(3):
            for j in range(4):
                if is_valid_state([i, j]):
                    p = Policy_Extraction([i, j])
                    policy[i][j] = p

    ar = np.asarray(grid, dtype=np.float32)
    figure, axis = plt.subplots()
    image = axis.imshow(ar, cmap='RdYlGn', interpolation='nearest')
    for i in range(3):
        for j in range(4):
            if i == 1 and j == 1:
                txt_display = "BIG WALL"
            elif (i == 0 and j == 3) or (i == 1 and j == 3):
                txt_display = "%.2f" % grid[i][j] + "\n" + "EXIT"
            else:
                txt_display = "%.2f" % grid[i][j] + "\n" + policy[i][j]

            text = axis.text(j, i, txt_display,
                             ha="center", va="center", color="black")

    plt.show()
