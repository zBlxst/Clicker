import requests

r = requests.get("http://musicfamily.org/realm/BuildingUpgrades/")

upgrades = list(map(lambda x: x.split("<area target=\"\" research=\"")[1].split("\" coords")[0].split("<p>"), filter(lambda x: "<area target=\"\" research=" in x, r.text.split("\n"))))
without_empty = list(map(lambda x: list(filter(lambda y: len(y), x)), upgrades))
pre_asc = list(filter(lambda x: "Upgrade" in x[0] and int(x[0].split("Upgrade ")[1].split(":")[0]) < 20, without_empty))

per_building = [pre_asc[i:i+19] for i in range(0, len(pre_asc), 19)]
bonus = per_building[25]
hall = per_building[24]
classic = per_building[:3] + per_building[10:17] +  per_building[24:25]
print(len(classic))
# print(len(per_building))
# print(list(map(len, per_building)))

reqs = [[] for _ in range(11)]
costs = [[] for _ in range(11)]
buffs = [[] for _ in range(11)]

for (i, building) in enumerate(classic):
    # print(f"Building {i}")
    for upgrade in building:
        req = int(upgrade[1].split(": ")[1].split(" ")[0])
        cost = int(upgrade[2].split(": ")[1].replace(",", "")) if "(" not in upgrade[2] else float(upgrade[2].split("(")[1].split(")")[0])
        buff = int(upgrade[4].split("by ")[1].split("%")[0])
        reqs[i].append(req)
        costs[i].append(cost)
        buffs[i].append(buff)
        # print(f"{req=} {cost=:.3e} {buff=}%")
        # for line in upgrade:
        #     print(line)
    # print()

print(f"static constexpr double UPGRADE_REQS[19] = {{{', '.join(list(map(str, reqs[i])))}}};")
for i in range(11):
    print(f"static constexpr double UPGRADE_COSTS_{i}[19] = {{{', '.join(list(map(str, costs[i])))}}};")
print(f"static constexpr double UPGRADE_BUFFS[19] = {{{', '.join(list(map(str, buffs[0])))}}};")