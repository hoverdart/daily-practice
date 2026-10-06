def first_revisited(stations: list[int]) -> int | None:
    """Return the first station encountered for the second time."""
    visited = set()
    for station in stations:
        if station in visited:
            return station
        visited.add(station)
    return None
