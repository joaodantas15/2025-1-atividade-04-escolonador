# Imagem base do Fedora
FROM fedora:latest

# Instala o compilador GCC, htop, perf e outras ferramentas
RUN dnf -y update && \
    dnf -y install gcc htop perf findutils fish && \
    dnf clean all

# Define o diretório de trabalho
WORKDIR /app

# Comando padrão para iniciar o shell
CMD ["fish"]
