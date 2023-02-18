BUFFER_SIZE = 10000

def is_prime(n):
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

def main():
    buffer = []
    count = 0
    for i in range(2, 65001):
        if is_prime(i):
            buffer.append(i)
            count += 1
    print("count:", count, ", last prime:", buffer[-1])

if __name__ == "__main__":
    main()
