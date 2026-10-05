def first_revisited(stations: list[int]) -> int | None:
    seen = set()
    for station in stations:
        if station in seen:
            return station
        seen.add(station)
    return None
