
def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    pq = [(0, start)]  # 优先队列（距离, 节点）
    
    while pq:
        current_dist, current_node = heapq.heappop(pq)
        if current_dist > distances[current_node]:
            continue
        
        for neighbor, weight in graph[current_node].items():
            distance = current_dist + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))
    
    return distances

graph = {
    'A': {'B': 4, 'C': 2},
    'B': {'D': 3, 'E': 1},
    'C': {'B': 1, 'D': 5},
    'D': {'E': 2},
    'E': {}
}
print(dijkstra(graph, 'A'))  # 输出：{'A':0, 'B':3, 'C':2, 'D':6, 'E':4}
