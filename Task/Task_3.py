from itertools import permutations

graph = {
    'U': [('V', 51), ('W', 56), ('X', 60), ('Y', 2), ('Z', 35)],
    'V': [('U', 51), ('W', 78), ('X', 13), ('Y', 51), ('Z', 68)],
    'W': [('U', 56), ('V', 78), ('X', 70), ('Y', 57), ('Z', 21)],
    'X': [('U', 60), ('V', 13), ('W', 70), ('Y', 61), ('Z', 68)],
    'Y': [('U', 2), ('V', 51), ('W', 57), ('X', 61), ('Z', 36)],
    'Z': [('U', 35), ('V', 68), ('W', 21), ('X', 68), ('Y', 36)]
}

vertices = ['U', 'V', 'W', 'X', 'Y', 'Z']

permutation_of_vertices = list(permutations(vertices))
shortest_tsp_path = []
shortest_tsp_path_length = float('INF')
for permutation in permutation_of_vertices:
    total_length = 0
    for i in range(len(permutation) - 1):
        vertex = permutation[i]
        next_vertex = permutation[i + 1]
        for edge in graph[vertex]:
            if edge[0] == next_vertex:
                total_length += edge[1]
                break
    # return to the starting vertex
    for edge in graph[permutation[-1]]:
        if edge[0] == permutation[0]:
            total_length += edge[1]
            break
    if total_length <= shortest_tsp_path_length:
        if len(shortest_tsp_path) == 0:
            shortest_tsp_path = permutation + (permutation[0],)
            shortest_tsp_path_length = total_length
            continue
        first_vertex = permutation[0]
        second_vertex = permutation[1]
        current_shortest_tsp_first_vertex = shortest_tsp_path[0]
        current_shortest_tsp_second_vertex = shortest_tsp_path[1]
        dist_current_shortest_tsp_first_with_second_vertex = None
        dist_first_vertex_with_second_vertex = None
        for edge in graph[current_shortest_tsp_first_vertex]:
            if edge[0] == current_shortest_tsp_second_vertex:
                dist_current_shortest_tsp_first_with_second_vertex = edge[1]
                break
        for edge in graph[first_vertex]:
            if edge[0] == second_vertex:
                dist_first_vertex_with_second_vertex = edge[1]
                break
        if dist_current_shortest_tsp_first_with_second_vertex < dist_first_vertex_with_second_vertex:
            continue
        shortest_tsp_path_length = total_length
        shortest_tsp_path = permutation + (permutation[0],)

        print('Shortest TSP path: ', shortest_tsp_path)
        print('Shortest TSP path length: ', shortest_tsp_path_length)

