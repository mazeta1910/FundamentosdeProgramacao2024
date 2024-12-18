CREATE DATABASE BD42SAvaliacao01;
GO

USE BD42SAvaliacao01;
GO

-- Criar a tabela Cidades
CREATE TABLE Cidades (
    id INT PRIMARY KEY IDENTITY,
    Cidade VARCHAR(255) NOT NULL,
    UF CHAR(2) NOT NULL
);

-- Inserir registros na tabela Cidades
INSERT INTO Cidades (Cidade, UF) VALUES ('Cidade A', 'SP');
INSERT INTO Cidades (Cidade, UF) VALUES ('Cidade B', 'RJ');
INSERT INTO Cidades (Cidade, UF) VALUES ('Cidade C', 'MG');

-- Criar a tabela Finalidades
CREATE TABLE Finalidades (
    id INT PRIMARY KEY IDENTITY,
    descricao VARCHAR(255) NOT NULL
);

-- Criar a tabela Fases
CREATE TABLE Fases (
    id INT PRIMARY KEY IDENTITY,
    descricao VARCHAR(50) NOT NULL
);

-- Criar a tabela Transformadores
CREATE TABLE Transformadores (
    id INT PRIMARY KEY IDENTITY,
    Nome VARCHAR(255) NOT NULL,
    TensaoEntrada FLOAT NOT NULL,
    TensaoSaida FLOAT NOT NULL,
    Custo MONEY NOT NULL,
    FaseId INT,
    FinalidadeId INT
);

-- Adicionar as restri��es de chave estrangeira
ALTER TABLE Transformadores ADD CONSTRAINT FK_Transformadores_Fases
FOREIGN KEY (FaseId) REFERENCES Fases(id);

ALTER TABLE Transformadores ADD CONSTRAINT FK_Transformadores_Finalidades
FOREIGN KEY (FinalidadeId) REFERENCES Finalidades(id);

-- Inserir registros na tabela Finalidades
INSERT INTO Finalidades (descricao) VALUES ('Elevar tens�o');
INSERT INTO Finalidades (descricao) VALUES ('Abaixar tens�o');
INSERT INTO Finalidades (descricao) VALUES ('Transformador de Corrente');

-- Inserir registros na tabela Fases
INSERT INTO Fases (descricao) VALUES ('Monof�sico');
INSERT INTO Fases (descricao) VALUES ('Bif�sico');
INSERT INTO Fases (descricao) VALUES ('Trif�sico');
INSERT INTO Fases (descricao) VALUES ('Polif�sico');

-- Criar a tabela Unidades
CREATE TABLE Unidades (
    id INT PRIMARY KEY IDENTITY,
    Nome VARCHAR(100) NOT NULL,
    Rua VARCHAR(255) NOT NULL,
    Numero INT NOT NULL,
    CEP VARCHAR(10) NOT NULL,
    CidadeID INT,
    FOREIGN KEY (CidadeID) REFERENCES Cidades(id)
);

-- Inserir registros na tabela Unidades(id, Nome, Rua, Numero, CEP, CidadeID), com suas respectivas restri��es de chave prim�riaeestrangeira
INSERT INTO Unidades (Nome, Rua, Numero, CEP, CidadeID) VALUES ('Unidade A', 'Rua A', 123, '12345-678', 1);
INSERT INTO Unidades (Nome, Rua, Numero, CEP, CidadeID) VALUES ('Unidade B', 'Rua B', 456, '98765-432', 2);
INSERT INTO Unidades (Nome, Rua, Numero, CEP, CidadeID) VALUES ('Unidade C', 'Rua C', 789, '54321-876', 3);


/*Listar os dados dos transformadores bif�sicos que est�o efetivamente instalados cuja finalidade seja elevar a tens�o em linguagem Sqrte*/
SELECT T.Nome, T.TensaoEntrada, T.TensaoSaida, T.Custo, F.descricao AS Finalidade FROM Transformadores T
INNER JOIN Fases F ON T.FaseId = F.id
INNER JOIN Finalidades Fin ON T.FinalidadeId = Fin.id
WHERE F.descricao = 'Bif�sico' AND Fin.descricao = 'Elevar tens�o' AND T.Custo > 0;
