from itertools import permutations

graph = {
  1: [2, 3, 5, 6],
  2: [4, 5],
  3: [2, 4, 5, 6],
  4: [1],
  5: [4, 6],
  6: [2, 4]
}

vertices = [1, 2, 3, 4, 5, 6]

def is_hamiltonian_path(path):
  """
  Check if a given path is a Hamiltonian path in the graph.
  """
  if len(path) != len(vertices):
    return False
  for i in range(len(path)-1):
    if path[i+1] not in graph[path[i]]:
      return False
  return True

hamiltonian_paths = []
permutation_of_vertices = list(permutations(vertices))
for path in permutation_of_vertices:
  if is_hamiltonian_path(path):
    hamiltonian_paths.append(path)

score = {
  1: 0,
  2: 0,
  3: 0,
  4: 0,
  5: 0,
  6: 0
}

for path in hamiltonian_paths:
  i = 0
  while i < len(path)-1:
    vertice = path[i]
    score[vertice] += (6-i)
    i += 1
  print(path)

print(score)


