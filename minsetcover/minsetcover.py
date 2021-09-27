import subprocess
import time

start = time.perf_counter()
proc = subprocess.run(['./minsetcover'])
end = time.perf_counter()
print('Tempo (s):', end - start)
