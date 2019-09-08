import plotly.graph_objects as go
from plotly.subplots import make_subplots
import numpy as np

def plot_levels(MAX_LEVEL = 30,
    MIN_LEVEL = 15,
    TOP_LEVEL = 50,
    measured_name = 'air_temperature',
    measured = [],
    area_names = {'bottom':'TOO COLD', 'top':'TOO HOT'},
    colors = {'top':'red','bottom':'blue'}):
    
    size = len(measured)
    x=np.linspace(0,size,size)

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=x, y=np.repeat(MIN_LEVEL,size),
                        fill='tonexty', fillcolor=colors['bottom'],
                        hoveron = 'points+fills', # select where hover is active
                        line_color=colors['bottom'],
                        text=area_names['bottom'],
                        hoverinfo = 'text',
                            name = area_names['bottom']))

    fig.add_trace(go.Scatter(x=x, y=np.repeat(MAX_LEVEL,size),
                        fill='none', 
                        hoveron='points',
                        line_color=colors['top'],
                        text=area_names['top'],
                        hoverinfo='text',
                            name = ''))

    fig.add_trace(go.Scatter(x=x, y=np.repeat(TOP_LEVEL,size),
                        fill='tonexty', 
                        fillcolor = colors['top'],
                        hoveron='points',
                        line_color=colors['top'],
                        text=area_names['top'],
                        hoverinfo='text',
                            name = area_names['top']))

    fig.add_trace(go.Scatter(x=x, y=measured,
                        fill='none', 
                        hoveron='points',
                        line_color='green',
                        text=measured_name,
                        hoverinfo='text+y',
                            name = measured_name))

    fig.update_layout(
        title=go.layout.Title(
            text='Measured ' + measured_name,
            xref="paper",
            x=0
        ),
        xaxis=go.layout.XAxis(
            title=go.layout.xaxis.Title(
                text="Index",
                font=dict(
                    family="Courier New, monospace",
                    size=18,
                    color="#7f7f7f"
                )
            )
        ),
        yaxis=go.layout.YAxis(
            title=go.layout.yaxis.Title(
                text=measured_name,
                font=dict(
                    family="Courier New, monospace",
                    size=18,
                    color="#7f7f7f"
                )
            )
        )
    )


    fig.update_layout(
        #title = "hover on <i>points</i> or <i>fill</i>",
        xaxis_range = [0,size],
        yaxis_range = [0,TOP_LEVEL]
    )
    fig.show()
    
    