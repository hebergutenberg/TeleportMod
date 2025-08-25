🌀 TeleportMod  

Um mod de teletransporte simples para **DayZ** que permite conectar locais de forma confiável — como bunkers secretos fora do mapa ou áreas personalizadas! 🗺️⚡ Originalmente criado para servidores privados, o mod inclui ativação por itens, consumo de recursos e muito mais.  

---

## ✨ Funcionalidades  

- ✅ **Pontos de teletransporte interativos** vinculados a qualquer objeto  
- 🔑 **Requisitos de itens** (ex: pé-de-cabra, cartão de acesso, pá)  
- ⚠️ **Dano ou consumo de itens** ao usar o teleporte  
- ⏳ **Ativação temporizada** – uso por tempo limitado  
- 🎵 **Efeitos sonoros** (em desenvolvimento – ainda não totalmente implementado)  
- 🖥️ **Transições de tela preta** com mensagens personalizadas  
- 🔄 **Sistema de cooldown** para evitar abuso  

---

## 🛠️ Exemplo de Configuração

```json
{
    "TeleportEntries": [
        {
            "EnableTeleport": 1,
            "TeleportName": "Entrada do Bunker Secreto",
            "ObjectType": "Land_Door_germa_1",
            "ObjectCoordinates": [7758.64, 16.18, 14116.90],
            "ObjectOrientation": [0.0, 0.0, 0.0],
            "TeleportPosition": [10.29, 10.76, 10.27],
            "CheckRadius": 1.0,
            "RequiredItem": "Crowbar",
            "RequiredItemDamagePercent": 50.0,
            "ConsumeRequiredItem": 0,
            "TeleportActiveTimeSeconds": 30,
            "MissingItemMessage": "🚫 Você precisa de um pé de cabra para forçar a porta!",
            "TeleportCooldownTimeSeconds": 60,
            "CooldownMessage": "🔒 A porta está trancada. Aguarde antes de tentar novamente.",
            "PreLoadRadius": 20.0,
            "TeleportDelaySeconds": 4,
            "IsUndergroundDestination": 1,
            "SafeGroundOffset": 1.5,
            "EnableBlackScreenEffect": 1,
            "BlackScreenDurationSeconds": 18,
            "BlackScreenMessage": "⚙️ Acessando instalação subterrânea... Aguarde.",
            "BlackScreenSoundFile": "",
            "EnableTeleportSound": 1,
            "TeleportSoundFile": "TeleportMod\\Data\\teleport_sound.ogg",
            "TeleportSoundRadius": 50.0,
            "TeleportSoundVolume": 1.0
        }
    ]
}
```

---

## 🧭 Parâmetros de Configuração

| Parâmetro | Descrição |
|---------------------------|----------------------------------------------------------------------|
| `EnableTeleport` | Ativa/desativa o teleporte (`1` = ✅, `0` = ❌) |
| `TeleportName` | Nome do teleporte para organização |
| `ObjectType` | Tipo de objeto que ativa o teleporte |
| `ObjectCoordinates` | 📍 Coordenadas do objeto ativador |
| `ObjectOrientation` | 🧭 Orientação do objeto (rotação) |
| `TeleportPosition` | 🎯 Coordenadas de destino do teleporte |
| `CheckRadius` | 📏 Raio de ativação do teleporte |
| `RequiredItem` | 🧰 Item necessário para ativação |
| `RequiredItemDamagePercent` | ⚠️ Dano aplicado ao item ao ser usado |
| `ConsumeRequiredItem` | Consome o item ao usá-lo (`1` = ✅, `0` = ❌) |
| `TeleportActiveTimeSeconds` | ⏱️ Tempo de ativação do teleporte (segundos) |
| `MissingItemMessage` | 💬 Mensagem sem o item necessário |
| `TeleportCooldownTimeSeconds` | ❄️ Tempo de recarga do teleporte |
| `CooldownMessage` | 💬 Mensagem durante recarga |
| `PreLoadRadius` | 🔄 Raio de pré-carregamento da área de destino |
| `TeleportDelaySeconds` | ⏳ Atraso antes do teleporte iniciar |
| `IsUndergroundDestination` | ⬇️ Destino é subterrâneo? (`1` = ✅, `0` = ❌) |
| `SafeGroundOffset` | 📐 Ajuste de altura para evitar spawn dentro do chão |
| `EnableBlackScreenEffect` | 🖥️ Ativa tela preta durante o teleporte |
| `BlackScreenDurationSeconds` | ⏱️ Duração da tela preta |
| `BlackScreenMessage` | 💬 Mensagem exibida na tela preta |
| `BlackScreenSoundFile` | 🔊 Som durante a tela preta |
| `EnableTeleportSound` | 🔊 Ativa som do teleporte |
| `TeleportSoundFile` | 🎵 Arquivo de som do teleporte |
| `TeleportSoundRadius` | 📣 Alcance do som |
| `TeleportSoundVolume` | 🔊 Volume do som |

---

## 🎮 Como Usar

1. **Posicione objetos** no mapa que servirão como ativadores de teleporte.  
2. **Configure as coordenadas e opções** no arquivo `config.json`.  
3. **Os jogadores interagem** com o objeto para teleportar (se tiverem o item necessário).  
4. **Itens podem ser danificados ou consumidos** conforme configurado.  

---

## 👥 Créditos e Agradecimentos  

Este mod é baseado no **[ActionTeleport](https://steamcommunity.com/sharedfiles/filedetails/?id=3405070168)** de **FreddyCruger** e **kenik**.  
Inclui um formato de configuração ampliado, novos recursos e correções de bugs.  

---

## 📜 Licença e Uso  

**Este mod é 100% gratuito** — assim como o original:  

- ✅ **Livre para uso** em qualquer servidor  
- ✅ **Pode ser modificado e redistribuído**  
- ✅ **Créditos são apreciados** ♥️  

---

## 🔄 Changelog  

### **Versão 1.1.0**  
- 🖥️ **Transições de tela preta** imersivas  
- ⏳ **Sistema de cooldown** configurável  
- 🔄 **Pré-carregamento de áreas** de destino  
- 🧩 **+15 parâmetros** de configuração por entrada  
- 🧠 **Lógica cliente/servidor separada**  
- 🟥 **Mensagens em vermelho/laranja** para melhor visibilidade  
- 🧹 **Correção de vazamentos de memória**  

### 🐛 Correções  
- ✅ Jogadores não spawnam mais dentro do chão  
- ✅ Teleportes funcionam após reinicialização do servidor  
- ✅ Itens não são consumidos múltiplas vezes  
- ✅ Mensagens agora aparecem corretamente no cliente  
- ✅ Recarregamento de cooldown corrigido  

---

💙 **Se gostou do mod, deixe um like ou comentário!**  
🔗 **Apoie o mod original: [ActionTeleport](https://steamcommunity.com/sharedfiles/filedetails/?id=3405070168)**  

*Feito com 💙 para a comunidade DayZ!*
