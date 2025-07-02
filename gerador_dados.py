# Importa as bibliotecas necessárias
import random
import string # Adicionamos a biblioteca 'string'

# --- Parâmetros ---
NUMERO_DE_REGISTROS = 10000
ARQUIVO_DE_SAIDA = "registros.txt"

# --- Listas de dados para gerar registros mais realistas ---
MODELOS_DE_CARROS = [
    "Gol", "Onix", "Strada", "HB20", "Argo", "Mobi", "Kwid", 
    "Creta", "T-Cross", "Compass", "Renegade", "Kicks", "Saveiro", 
    "Monza", "J3", "Uno", "Gorgel", "Amarok"
]

CORES = [
    "Preto", "Branco", "Prata", "Cinza", "Vermelho", "Azul", "Marrom"
]

# --- Início do Script ---
print(f"Iniciando a geração de {NUMERO_DE_REGISTROS} registros...")

# Conjuntos para garantir a unicidade de renavams e placas
renavams_unicos = set()
placas_unicas = set() # NOVO: Conjunto para garantir placas únicas

# Lista para armazenar todos os registros que vamos criar
registros_finais = []

# Loop para criar cada um dos 10.000 registros
for i in range(NUMERO_DE_REGISTROS):
    
    # 1. Gera um Renavam único de 11 dígitos
    renavam = None
    while renavam is None or renavam in renavams_unicos:
        renavam = random.randint(10000000000, 99999999999)
    renavams_unicos.add(renavam)

    # 2. NOVO: Gera uma Placa única no formato XXX0X00
    placa = None
    while placa is None or placa in placas_unicas:
        # Gera a placa parte por parte
        p1 = "".join(random.choice(string.ascii_uppercase) for _ in range(3))
        p2 = random.choice(string.digits)
        p3 = random.choice(string.ascii_uppercase)
        p4 = "".join(random.choice(string.digits) for _ in range(2))
        placa = f"{p1}{p2}{p3}{p4}"
    placas_unicas.add(placa)

    # 3. Sorteia os outros dados do carro
    modelo = random.choice(MODELOS_DE_CARROS)
    ano = random.randint(1990, 2024)
    cor = random.choice(CORES)

    # 4. ATUALIZADO: Formata o registro com os 5 campos
    linha_registro = f"{renavam},{placa},{modelo},{ano},{cor}\n"
    registros_finais.append(linha_registro)

# --- Escrita dos dados no arquivo ---
try:
    with open(ARQUIVO_DE_SAIDA, "w", encoding="utf-8") as arquivo:
        arquivo.writelines(registros_finais)
    
    print(f"Sucesso! O arquivo '{ARQUIVO_DE_SAIDA}' foi criado com {len(registros_finais)} registros.")
    print("Cada linha agora contém: renavam,placa,modelo,ano,cor")

except Exception as e:
    print(f"Ocorreu um erro ao escrever o arquivo: {e}")