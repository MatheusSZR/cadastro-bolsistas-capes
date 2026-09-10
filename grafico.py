import matplotlib.pyplot as plt

n = [10, 20, 40, 80, 160]
comparacoes = [45, 190, 780, 3160, 12720]

plt.plot(n, comparacoes, marker="o")

for x, y in zip(n, comparacoes):
    plt.annotate(
        str(y),
        (x, y),
        textcoords="offset points",
        xytext=(0, 8),
        ha="center"
    )

plt.title("Número de comparações em função da quantidade de nomes")
plt.xlabel("Quantidade de nomes inseridos")
plt.ylabel("Número de comparações")

plt.grid(True)
plt.savefig("grafico_comparacoes.png", dpi=300, bbox_inches="tight")
plt.show()