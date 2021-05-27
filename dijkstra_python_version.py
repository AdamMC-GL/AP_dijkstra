def wait_for_command():


def alles():
    def dijkstra(graph, start, goal):

        kleinste_afstand_lengte = {}
        vorige_nodes = {}
        Nog_te_bekijken_nodes = graph
        infinity = float('inf')
        path = []
        for node in Nog_te_bekijken_nodes:
            kleinste_afstand_lengte[node] = float('inf')
        kleinste_afstand_lengte[start] = 0

        while Nog_te_bekijken_nodes: # dit doen tot dat de lijst Nog_te_bekijken_nodes leeg is

             # om te beslissen welk node op het moment het kleinst is
            minNode = None # het kleinste node is nog niet gekozen
            for node in Nog_te_bekijken_nodes: # dit steeds doen voor alle nodes die nog niet zijn berekend
                if minNode is None:
                    minNode = node # de eerste de beste node word voor nu aangewezen als kleinste node
                elif kleinste_afstand_lengte[node] < kleinste_afstand_lengte[minNode]: # elke keer word gekeken of de bekeken node kleiner is dan de current kleinste node
                    minNode = node # als dat zo is word dat dan de current kleinste node

                # hierna is het kleinste node gekozen
            # om te kijken of de aanliggende nodes een beter pad krijgen via the current node:
            for childNode, weight in graph[minNode].items():# kleinste node is gekozen nu, nu word er gekeken naar de paden van die node
                if weight + kleinste_afstand_lengte[minNode] < kleinste_afstand_lengte[childNode]:
                    kleinste_afstand_lengte[childNode] = weight + kleinste_afstand_lengte[minNode]
                    vorige_nodes[childNode] = minNode
            Nog_te_bekijken_nodes = removekey(Nog_te_bekijken_nodes, minNode)

        currentNode = goal
        while currentNode != start:
            path.insert(0, currentNode)
            currentNode = vorige_nodes[currentNode]
        path.insert(0, start)
        if kleinste_afstand_lengte[goal] != infinity:
            score = kleinste_afstand_lengte[goal]
            return score, path

    def removekey(d, key):
        r = dict(d)
        del r[key]
        return r


    #graph1 = {'a': {'b': 2, 'c': 1, 'e':5}, 'b': {'a': 2, 'd': 3}, 'c': {'a': 1, 'd': 5}, 'd': {'c': 5, 'b':3}, 'e': {'a': 5, 'b':1}}




    graph1 = {'0': {'1': 1, '2': 1, '3': 1, '4': 1},
              '1': {'0' : 1, '7' : 1, '8' : 1},
              '2': {'0' : 1, '7' : 1, '8' : 1},
              '3': {'0': 1, '5': 1,  '6': 1},
              '4': {'0': 1, '5': 1,  '6': 1},
              '5': {'3': 1, '4': 1},
              '6': {'3': 1, '4': 1},
              '7': {'1': 1, '2': 1},
              '8': {'1': 1, '2': 1},
              }


    #code om de list 'open_spaces' te veranderen op basis van de database

    open_spaces=['1']




    bestscore=float('inf')

    for scores in open_spaces:
        winner = dijkstra(graph1, '0', scores)
        if bestscore > winner[0]:
            bestscore = winner[0]
            bestpath = winner[1]

    print('De dichtbijste open plek is: '+ bestpath[-1])
    print('En je komt daar via '+ str(bestpath))


    print('\n\n\n')
    print(dijkstra(graph1, '0', '8'))


    def send_data(space):
        import socket

        UDP_IP = "172.20.10.10"
        UDP_PORT = 5005
        MESSAGE = str(space)
        print("UDP 172.20.10.10:" + UDP_IP)
        print("UDP 5005:" + str(UDP_PORT))
        print("message:" + MESSAGE)
        sock = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_DGRAM)  # UDP
        UDP_IP = UDP_IP.encode()
        MESSAGE = MESSAGE.encode()
        sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

    chosenspace = int(bestpath[-1])
    send_data(chosenspace)

alles()

