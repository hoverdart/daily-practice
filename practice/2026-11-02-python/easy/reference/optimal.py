def prefix_route_counts(routes: list[str], queries: list[str]) -> list[int]:
    root = {"count": 0, "next": {}}

    for route in routes:
        node = root
        node["count"] += 1
        for ch in route:
            node = node["next"].setdefault(ch, {"count": 0, "next": {}})
            node["count"] += 1

    result = []
    for prefix in queries:
        node = root
        for ch in prefix:
            node = node["next"].get(ch)
            if node is None:
                break
        result.append(node["count"] if node is not None else 0)
    return result
