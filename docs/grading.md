
**ВАЖНО: до конца сентября этот документ будет драфтом и может претерпеть изменения**


# Система оценивания

Оценки по всем активностям будут выставляться в главную ведомость.

### Летучки

* Для кого: опционально

Баллы за летучки **бонусные**.
*Это означает, что их отсутсвие не будет негативно сказываться на общей оценке.*

- Максимальный балл (`maxL`) за летучку рассчитывается как `1 / количество_летучек`
- Балл за `i`-ю летучку (`L_i`) рассчитывается как `(количество_верных_ответов / количество_вопросов) * maxL`
- Итоговый балл за летучки --- это сумма всех баллов за летучки: `L = L_1 + ... + L_n`

Эти бонусы можно будет распределить между дорешками (`Ld`), контрольными (`Lc`) и большими дз (`Lhw`), а так же между экзаменационными активностями - теормин (`Etm`), теория (`Et`) и задача (`Ea`) :

`L == Ld + Lc + Lhw + Etm + Et + Ea`

---

### Дорешки

see [about_cls.md](/docs/about_activities/about_cls.md)

### Контрольные работы

see [about_control.md](/docs/about_activities/about_contol.md)

### Большие домашние задания

* Для всех студентов
* Код-ревью: да, 3 итерации

За каждое домашнее задание можно получить либо зачет (`1` балл), либо незачет (`0` баллов)

Помимо этого могут быть дополнительные задания, за которые даются бонусные баллы. Бонусы можно получить только в случае зачета.

Итоговая оценка за большие домашние задания: `2 + баллы_за_дз + Lhw`

---

### Экзамен

Необходимое условие для допуска к экзамену: `>=2.5` за каждую из следующих активностей: дорешки, контрольные, большие дз.

Если `< 2.5` только за одну из активностей, то можно будет получить допуск во время экзамена.

#### Экзамен (offline, очная форма)

Экзамен состоит из 3 блоков: теормин, теория, задача.  За каждый из блоков можно получить максимум 5 баллов. Оценка может быть десятичной, например 2.5, 3.5, 4.5.

Если оценка за каждый из блоков `>= 2.5`, то оценка за экзамен рассчитывается как взвешенное среднее оценок этих блоков, иначе `2`.

#### Экзамен (online, заочная форма)

Экзамен состоит из 2 блоков: теортест, задача. За каждый из блоков можно получить максимум 5 баллов. Оценка может быть десятичной, например 2.5, 3.5, 4.5.

Если оценка за каждый из блоков `>= 2.5`, то оценка за экзамен рассчитывается как взвешенное среднее оценок этих блоков, иначе `2`.

---

### Итоговая оценка за курс

Оценка за основные активности: `activities = AVG(дорешки, контрольные, большие дз)`

Итоговая оценка: `AVG(activities, exam)`

# Обозначения

- `offline` - студенты очной формы обучения
- `online` - студенты, обучающиеся на онлайн-программе
