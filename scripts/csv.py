def read_csv(path):

    with open(path) as csvf:
        lines = csvf.readlines()

    lines = [line for line in lines if not line.startswith('#')]
    headers = lines[0].split(',')
    lines = lines[1:]
    column_data = list(zip(*[line.split(',') for line in lines]))

    for i, col in enumerate(column_data):
        try:
            fcol = [float(coli) if coli.strip() else float('nan') for coli in col]
            column_data[i] = fcol
        except:
            pass

    data = {hdr:col for hdr,col in zip(headers,column_data)}
    return data
